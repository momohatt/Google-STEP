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

    stack.append({'priority':-1})

    while index < len(tokens):
        if tokens[index]['type']=='BRACKET_HEAD':
            stack.append(tokens[index])
        elif tokens[index]['type']=='BRACKET_TAIL':
            while stack[-1]['type']!='BRACKET_HEAD':
                postPrefixTokens.append(stack.pop())
            del stack[-1]
        else:
            while tokens[index]['priority']<=stack[-1]['priority']:
                postPrefixTokens.append(stack.pop())
            
            stack.append(tokens[index])
        
        index+=1
    
    while stack[-1]['priority']!=-1:
        postPrefixTokens.append(stack.pop())

    return postPrefixTokens


def evaluate(tokens):
    answer = 0
    index = 0
    stack = []

    while index < len(tokens):
        if(tokens[index]['type']=='NUMBER'):
            stack.append(tokens[index])
        elif(tokens[index]['type']=='PLUS'):
            tmp=stack.pop()['number']
            tmp+=stack.pop()['number']
            stack.append({'number':tmp})
        elif(tokens[index]['type']=='MINUS'):
            tmp=-1.0*stack.pop()['number']
            tmp+=stack.pop()['number']
            stack.append({'number':tmp})
        elif(tokens[index]['type']=='MULTIPLY'):
            tmp=stack.pop()['number']
            tmp*=stack.pop()['number']
            stack.append({'number':tmp})
        elif(tokens[index]['type']=='DIVIDE'):
            tmp=1.0/stack.pop()['number']
            tmp*=stack.pop()['number']
            stack.append({'number':tmp})
        else:
            print 'calculation error'
         
        index+=1

    return stack.pop()['number']


def test(line, expectedAnswer):
    tokens = tokenize(line)
    postPrefixTokens = convertToPostPrefixFormat(tokens)
    actualAnswer = evaluate(postPrefixTokens)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    print "==== Test started! ===="
    test("1+2", 3)
    test("1.0+2.1-3", 0.1)
    test("1.2+3.6/2", 3.0)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    postPrefixTokens = convertToPostPrefixFormat(tokens)
    answer = evaluate(postPrefixTokens)
    print "answer = %f\n" % answer
    #print postPrefixTokens
