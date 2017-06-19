def readNumber(line, index):
    """
    recognizes numbers and makes them into tokens
    takes string numerical figure and int index
    returns tokenized numerical figure and index
    """
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
    token = {'type': 'NUMBER', 'number': number, 'priority':4}
    return token, index


def readOperator(figure, index):
    """
    recognizes operators (including brackets) and makes them into tokens
    takes string figure and int index
    returns tokenized operators or false (only when there are any invalid characters)
    """
    if figure == '+':
        token = {'type': 'PLUS', 'priority':1}
    elif figure == '-':
        token = {'type': 'MINUS', 'priority':1}
    elif figure == '*':
        token = {'type': 'MULTIPLY', 'priority':2}
    elif figure == '/':
        token = {'type': 'DIVIDE', 'priority':2}
    elif figure == '^':
        token = {'type': 'POWER', 'priority':3}
    elif figure == '(':
        token = {'type': 'BRACKET_HEAD', 'priority':0}
    elif figure == ')':
        token = {'type': 'BRACKET_TAIL', 'priority':0}
    else: #when an invalid character is found
        raise TypeError("Invalid character found:", figure)
    return token, index + 1


def tokenize(line):
    """
    splits numerical formula string into tokens
    takes string numerical formula
    returns an array of tokens
    """
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        else:
            (token, index) = readOperator(line[index], index)
        tokens.append(token)
    return tokens


def convertToPostfixFormat(tokens):
    """
    converts formula of tokens written in infix notation into the one in postfix notation
    takes an array of tokens
    returns an array of tokens
    """
    postfixTokens=[]
    stack=[]
    index = 0

    stack.append({'priority':-1})

    while index < len(tokens):
        if tokens[index]['type']=='BRACKET_HEAD':
            stack.append(tokens[index])
        elif tokens[index]['type']=='BRACKET_TAIL':
            while stack[-1]['type']!='BRACKET_HEAD':
                postfixTokens.append(stack.pop())
            del stack[-1]
        else:
            while tokens[index]['priority']<=stack[-1]['priority']:
                postfixTokens.append(stack.pop())
            
            stack.append(tokens[index])
        
        index+=1
    
    while stack[-1]['priority']!=-1:
        postfixTokens.append(stack.pop())

    return postfixTokens


def evaluate(tokens):
    """
    calculates the numerical formula written in postfix notation and returns the result
    takes an array of tokens
    returns a double number
    """
    
    index = 0
    stack = []

    while index < len(tokens):
        if(tokens[index]['type'] == 'NUMBER'):
            stack.append(tokens[index])
        elif(tokens[index]['type'] == 'PLUS'):
            tmp = stack.pop()['number']
            tmp += stack.pop()['number']
            stack.append({'number': tmp})
        elif(tokens[index]['type'] == 'MINUS'):
            tmp = -1.0 * stack.pop()['number']
            tmp += stack.pop()['number']
            stack.append({'number': tmp})
        elif(tokens[index]['type'] == 'MULTIPLY'):
            tmp = stack.pop()['number']
            tmp *= stack.pop()['number']
            stack.append({'number': tmp})
        elif(tokens[index]['type'] == 'DIVIDE'):
            tmp = 1.0 / stack.pop()['number']
            tmp *= stack.pop()['number']
            stack.append({'number': tmp})
        elif(tokens[index]['type'] == 'POWER'):
            power = stack.pop()['number']
            tmp = stack.pop()['number'] ** power
            stack.append({'number': tmp})
        else:
            print 'calculation error'
         
        index+=1

    return stack.pop()['number']


def test(line, expectedAnswer):
    """
    examines if the functions work correctly and prints out the result
    takes string numerical formula and an int (expected answer)
    returns nothing
    """
    tokens = tokenize(line)
    postfixTokens = convertToPostfixFormat(tokens)
    actualAnswer = evaluate(postfixTokens)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    """
    conducts the test and prints out the result. done before the main function
    takes nothing
    returns nothing
    """
    print "==== Test started! ===="
    test("1", 1.0)
    test("1+2", 3.0)
    test("1+2.0", 3.0)
    test("1.0+2", 3.0)
    test("1.0+2.0", 3.0)

    test("1-2", -1.0)
    test("1-2.0+3", 2.0)
    test("1.0+2.1-3", 0.1)

    test("3*2", 6.0)
    test("4/2", 2.0)
    test("1+2*3", 7.0)
    test("1*2+3*4", 14.0)
    test("1/2+3/4", 1.25)

    test("3^2", 9.0)
    test("2^5-1", 31.0)
    test("2^5/4", 8.0)

    test("(1)", 1.0)
    test("(1+2)*(3+4)", 21.0)
    test("(1+(2-3)*4)*5", -15.0)
    test("(1+(2-3)^4)*5", 10.0)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    postfixTokens = convertToPostfixFormat(tokens)
    answer = evaluate(postfixTokens)
    print "answer = %f\n" % answer
    #print postfixTokens
