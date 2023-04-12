#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE 1000
typedef int element;
typedef struct {
	element data[MAX_SIZE];
	int top;
}stacktype;

void init_stack(stacktype* s)
{
	// s�� ����Ű�� stacktype����ü�� ž�� ���� -1�� �����Ѵ�.
	s->top = -1;
}

int is_empty(stacktype* s)
{
	return (s->top == -1);
}
int is_full(stacktype* s)
{
	return (s->top == (MAX_SIZE - 1));
}
void push(stacktype* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "Stack Full!\n");
		return;
	}
	else
	{
		s->data[++s->top] = item;
	}
}
element pop(stacktype* s)
{
	if (is_empty(s))
	{

		exit(1);
	}
	else return s->data[(s->top)--];
}
element peek(stacktype* s)
{
	if (is_empty(s))
	{
		exit(1);
	}
	else return s->data[s->top];
}
int prec(char op)
{
	switch (op)
	{
	case '(':case')': return 0;
	case '+':case'-': return 1;
	case '*':case'/': return 2;
	default:
		printf("������ ����");
		break;
	}
}
void infix_to_postfix(char exp[], char postfix_exp[])//fix_to_postfix �Լ����� ��ȯ�� postfix ǥ����� ������ eval �Լ��� ���ڷ� �����ؾ� �Ѵ�.
//�̸� ���� main �Լ������� infix_to_postfix �Լ��� ȣ���ϱ� ���� postfix �迭�� �����ϰ�, infix_to_postfix �Լ� ������ postfix �迭�� postfix ǥ����� ������ �����ϵ��� �����ؾ� �Ѵ�. 
{
	int j = 0;
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);//exp[]�� �ȵȴ� strlen()�� ()���̿��� ���� ��ü�� �����ؾ���. �� �Լ��� �Ű������� ���ڿ��� �ּҰ��� �����ؾ���. 
	stacktype s; //s��� ����ü Ÿ���� ����� ���̱� ������ �ʿ���
	init_stack(&s);
	for (i; i < len; i++)
	{
		ch = exp[i];
		switch (ch)
		{

		case '+':case'-':case'*':case'/':
			if (exp[0] == '+' || exp[0] == '-' || exp[0] == '*' || exp[0] == '/')
			{
				printf("Error: Invalid expression");
				exit(1);
			}
			if (!is_empty(&s) && prec(ch) <= prec(peek(&s)))
			{
				postfix_exp[j++] = pop(&s);
			}
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			do
			{
				top_op = pop(&s);
				postfix_exp[j++] = top_op;
				top_op = pop(&s);
			} while (top_op != '(');
			break;

		default:
			if (isdigit(ch))
			{
				int num = ch - '0';
				while (i + 1 < len && isdigit(exp[i + 1]))
				{
					num = num * 10 + (exp[i + 1] - '0');
					i++;
				}
				postfix_exp[j++] = num + '0';
			}
			else
			{
				printf("error: invalid expression");
				exit(1);
			}
			break;
		}
	}
	while (!is_empty(&s))
	{
		postfix_exp[j++] = pop(&s);
	}
	postfix_exp[j] = '\0';
	printf("postfix expression is: %s", postfix_exp);
}
void remove_spaces(char exp[])
{
	int i, j = 0;
	for (i = 0; exp[i] != '\0'; i++)
	{
		if (exp[i] != ' ')
			exp[j++] = exp[i];
	}
	exp[j] = '\0';
}
int eval(char exp[])
{
	int op1, op2, i;
	int len = strlen(exp);
	char ch;
	stacktype s;
	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (isdigit(ch))
		{
			ch = ch - '0';
			push(&s, ch);
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+':
				push(&s, op1 + op2); break;
			case '-':
				push(&s, op1 - op2); break;
			case '*':
				push(&s, op1 * op2); break;
			case '/':
				push(&s, op1 / op2); break;
			}
		}
		else if (ch == ' ')
			continue;
		else
		{
			printf("Error: Mismatched parentheses");
			exit(1);
		}
	}
	return pop(&s);
}

int main(void)
{
	int result;
	char a[400];
	char b[400];
	printf("Enter an infix expression:");
	scanf("%s", &a);
	remove_spaces(a);
	infix_to_postfix(a, b);
	printf("\n");
	result = eval(b);
	printf("Result: %d", result);
	return 0;
}