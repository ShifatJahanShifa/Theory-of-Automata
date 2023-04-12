#include<bits/stdc++.h>
using namespace std;

#define Z 'Z'
#define CAN_NOT_POP -1
int q0=0, q1=1, qf=2;
int EMPTY_STACK_BUT_STRING_REMAINS=100;
stack<int>pda_stack;

//https://scanftree.com/automata/npda-for-ww-to-power-R

int pushDelta(int currentState, char alphabet, char stackTop)
{
    if(currentState==q0 && alphabet=='a' && stackTop==Z)
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else if(currentState==q0 && alphabet=='a' && stackTop=='a')
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else if(currentState==q0 && alphabet=='b' && stackTop==Z)
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else if(currentState==q0 && alphabet=='b' && stackTop=='b')
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else if(currentState==q0 && alphabet=='a' && stackTop=='b')
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else if(currentState==q0 && alphabet=='b' && stackTop=='a')
    {
        printf("push delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.push(alphabet);
        return q0;
    }
    else
    {
        printf("Unknown Push_Delta command!\n");
        exit(1);
    }
}

int popDelta(int currentState, char alphabet, char stackTop)
{
    if(currentState==q0 && alphabet=='a' && stackTop=='a')
    {
        printf("pop delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.pop();
        return q1;
    }
    else if(currentState==q0 && alphabet=='b' && stackTop=='b')
    {
        printf("pop delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.pop();
        return q1;
    }
    else if(currentState==q1 && alphabet=='b' && stackTop=='b')
    {
        printf("pop delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.pop();
        return q1;
    }
    else if(currentState==q1 && alphabet=='a' && stackTop=='a')
    {
        printf("pop delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        pda_stack.pop();
        return q1;
    }
    else if(currentState==q1 && alphabet=='\0' && stackTop==Z)
    {
        printf("pop delta  (%d,%c,%c)\n",currentState, alphabet, stackTop);
        return qf;
    }
    else
    {
        return CAN_NOT_POP;
    }
}

void clearStack()
{
    while(!pda_stack.empty())
        pda_stack.pop();
}

bool npda(string input)
{
    bool ok = false;

    for(int assumedMidPoint = 1; assumedMidPoint<input.size()-1; assumedMidPoint++)
    {
        int currentState = q0;
        clearStack();
        pda_stack.push(Z);

        printf("\nAssumed mid = %d \n\n",assumedMidPoint);

        int i=0;
        for(i=0; i<input.size(); i++)
        {
            if(i<assumedMidPoint)
                currentState = pushDelta(currentState, input[i], pda_stack.top());
            else if(i>=assumedMidPoint)
                currentState = popDelta(currentState, input[i], pda_stack.top());

            if(pda_stack.size()==1)
            {

                ok=false;
                break;
            }
            else if(currentState==CAN_NOT_POP)
            {
                ok=false;
                break;
            }
        }

        currentState = popDelta(currentState, '\0', pda_stack.top());
        if(currentState==qf && i==input.size()-1)
            return true;
    }
    return ok;
}

int main()
{
    string input;
    cin>>input;
    cout<<npda(input)<<endl;

    return 0;
}

