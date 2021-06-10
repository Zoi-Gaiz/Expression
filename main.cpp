#include <windows.h>
#include <stack>
#include <string>
#include <iostream>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
using namespace std;


//给字符串增加一个标记
void AddFlag(wchar_t *expression);

//中缀表达式转换为后缀表达式
void Postfix(wchar_t *expression);

//优先级比较,c1栈顶运算符，c2当前扫描读到的运算符
wchar_t PreorityCmp(wchar_t c1, wchar_t c2);

//计算表达式
bool Calculate(wchar_t *expression, wchar_t *result);

//是运算符返回1，否则返回0
int IsOperator(wchar_t c);

//计算,前3个参数为入参数,最后一个为出参,返回1操作成功,返回0操作失败
double Calc(double first, double second, wchar_t op);

void AddFlag(wchar_t *expression) {
    wchar_t expTmp[MAXBYTE] = {0};
    unsigned posTmp = 0;
    expTmp[0] = expression[0];
    unsigned iLength = wcslen(expression);
    for (size_t pos = 1; pos < iLength; ++pos) {
        if ((isdigit(expression[pos - 1]) && expression[pos] != '.')
            && !isdigit(expression[pos])
                )
            expTmp[++posTmp] = '#';
        expTmp[++posTmp] = expression[pos];
    }
    if (isdigit(expression[iLength - 1])) {
        expTmp[++posTmp] = '#';
    }
    wcscpy(expression, expTmp);
}

void Postfix(wchar_t *expression) {
    stack<wchar_t> cstack;
    wstring strPostfix = L"";
    for (size_t pos = 0; pos < wcslen(expression);) {
        if (isdigit(expression[pos]) || expression[pos] == '#' || expression[pos] == '.') {
            strPostfix += expression[pos];
            ++pos;
        } else {
            if (cstack.empty()) {
                cstack.push(expression[pos]);
                ++pos;
            } else if (PreorityCmp(cstack.top(), expression[pos]) == '<') {
                cstack.push(expression[pos]);
                ++pos;
            } else if (PreorityCmp(cstack.top(), expression[pos]) == '>') {

                wchar_t c = cstack.top();
                cstack.pop();
                strPostfix += c;
            } else if (PreorityCmp(cstack.top(), expression[pos]) == '=') {
                cstack.pop();
                ++pos;
            }
        }
    }
    while (!cstack.empty()) {
        strPostfix += cstack.top();
        cstack.pop();
    }

    wcscpy(expression, strPostfix.c_str());
}

wchar_t PreorityCmp(wchar_t c1, wchar_t c2) {
    wchar_t cResult = '=';
    wstring strBig = L"++,+-,+),-+,--,-),*+,*-,**,*//,*),//+,//-,//*,////,//),)+,)-,)*,)//,)),";
    wstring strSmall = L"+*,+//,+(,-*,-//,-(,*(,//(,(+,(-,(*,(//,((,";
    wstring strEqual = L"()";
    wstring str = L"";
    str = c1;
    str += c2;
    if (strBig.npos != strBig.find(str))
        cResult = '>';
    else if (strSmall.npos != strSmall.find(str))
        cResult = '<';
    else;
    return cResult;
}

bool Calculate(wchar_t *expression, wchar_t *result) {
    stack <wstring> pcStack;
    wchar_t cValue[MAXBYTE] = {0};
    unsigned num = 0;
    for (size_t pos = 0; pos < wcslen(expression); ++pos) {
        if (isdigit(expression[pos]) || expression[pos] == '.') {
            cValue[num++] = expression[pos];
        } else if (expression[pos] == '#') {
            pcStack.push(cValue);
            memset(cValue, 0, MAXBYTE);
            num = 0;
        } else if (IsOperator(expression[pos])) {
            if (pcStack.empty())
                return false;
            double second = _wtof(pcStack.top().c_str());
            pcStack.pop();
            if (pcStack.empty())
                return false;
            double first = _wtof(pcStack.top().c_str());
            pcStack.pop();
            wchar_t cRet[MAXBYTE] = {0};
            double result = Calc(first, second, expression[pos]);
            swprintf(cRet, L"%lf", result);
            pcStack.push(cRet);
        }
    }
    wcscpy(result, pcStack.top().c_str());
    return true;
}


double Calc(double first, double second, wchar_t op) {
    double iResult;
    switch (op) {
        case '+':
            iResult = first + second;
            break;
        case '-':
            iResult = first - second;
            break;
        case '*':
            iResult = first * second;
            break;
        case '/':
            iResult = first / second;
            break;
    }
    return iResult;
}

int IsOperator(wchar_t c) {
    return (c == '+' || c == '-' || c == '*' || c == '/') ? 1 : 0;
}

void ExpRun() {
    wchar_t n[100], m[100];
    memset(n, 0, sizeof(n));
    memset(m, 0, sizeof(m));
    wcin >> n;
    AddFlag(n);
    Postfix(n);
    Calculate(n, m);
    wcout << m << endl;
}


int main() {
    ExpRun();
}
