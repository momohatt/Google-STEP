def readNumber(line, index):
    number = 0
    while index < len(line) and line[index].isdigit():
        number = number * 10 + int(line[index])
        index += 1
    if index < len(line) and line[index] == '.':
        index += 1
        keta = 0.1
        while index < len(line) and line[index].isdigit():
            number += int(line[index]) * keta
            keta *= 0.1
            index += 1
    token = {'type': 'NUMBER', 'number': number, 'priority':3}
    return token, index


def readPlus(line, index):
    token = {'type': 'PLUS', 'priority':1}
    return token, index + 1


def readMinus(line, index):
    token = {'type': 'MINUS', 'priority':1}
    return token, index + 1


def readMultiply(line, index):
    token = {'type': 'MULTIPLY', 'priority':2}
    return token, index + 1


def readDivide(line, index):
    token = {'type': 'DIVIDE', 'priority':2}
    return token, index + 1


def readBracketHead(line, index):
    token = {'type': 'BRACKET_HEAD', 'priority':0}
    return token, index + 1


def readBracketTail(line, index):
    token = {'type': 'BRACKET_TAIL'}
    return token, index + 1


def tokenize(line):
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        elif line[index] == '+':
            (token, index) = readPlus(line, index)
        elif line[index] == '-':
            (token, index) = readMinus(line, index)
        elif line[index] == '*':
            (token, index) = readMultiply(line, index)
        elif line[index] == '/':
            (token, index) = readDivide(line, index)
        elif line[index] == '(':
            (token, index) = readBracketHead(line, index)
        elif line[index] == ')':
            (token, index) = readBracketTail(line, index)
        else:
            print 'Invalid character found: ' + line[index]
            exit(1)
        tokens.append(token)
    return tokens


def convertToPostPrefixFormat(tokens):
    postPrefixTokens=[]
    stack=[]
    index = 0

    stack.append({'priority':3})
    postPrefixTokens.append({'priority':3})

    while index < len(tokens):
        if tokens[index]['type']=='BRACKET_HEAD':
            stack.append(tokens[index])
        elif tokens[index]['type']=='BRACKET_TAIL':
            while stack[-1]['type']!='BRACKET_HEAD':
                postPrefixTokens.append(stack.pop())
        else:
            #print index
            while tokens[index]['priority']<=stack[-1]['priority']: #list index out of range
                postPrefixTokens.append(stack.pop())
            
            stack.append(tokens[index])

        #print 'stack'
        #print stack
        
        index+=1
    
    while sp1 > 0:
        sp2+=1
        postPrefixTokens[sp2]=stack[sp1]
        sp1-=1
    
    del postPrefixTokens[0]

    return postPrefixTokens


def evaluate(tokens):
    answer = 0
    tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
    index = 1
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'PLUS':
                answer += tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MINUS':
                answer -= tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MULTIPLY':
                answer *= tokens[index]['number']
            elif tokens[index -1]['type'] == 'DIVIDE':
                answer /= tokens[index]['number']
            else:
                print 'Invalid syntax'
        index += 1
    return answer


def test(line, expectedAnswer):
    tokens = tokenize(line)
    actualAnswer = evaluate(tokens)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    print "==== Test started! ===="
    test("1+2", 3)
    test("1.0+2.1-3", 0.1)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    postPrefixTokens = convertToPostPrefixFormat(tokens)
    #answer = evaluate(postPrefixTokens)
    print "answer = %f\n" % postPrefixTokens
