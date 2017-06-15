def convertToPostPrefixFormat(tokens):
    postPrefixTokens=[]
    stack=[]
    sp1=sp2=0 #stackpointer
    index = 0

    while index < len(tokens):
        if tokens[index]['type']=='BRACKET_HEAD':
            sp1+=1
            stack[sp1]==tokens[index]
        elif tokens[index]['type']=='BRACKET_TAIL':
            while stack[sp1]['type']!='BRACKET_HEAD':
                sp2+=1
                sp1-=1
                postPrefixTokens[sp2]=stack[sp1]
        else:
            while tokens[index]['priority']<=stack[sp1-1]['priority']:
                sp2+=1
                sp1-=1
                postPrefixTokens[sp2]=stack[sp1]
            sp1+=1
            stack[sp1]=tokens[index]

        index+=1

    while sp1 > 0:
        postPrefixTokens[sp2+1]=stack[sp1]
        sp1-=1

    return postPrefixTokens

