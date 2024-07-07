#include <iostream>
#include <ctime>

using namespace std;

enum enQuestionLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};
enum enOperationType
{
    Addition = 1,
    Subtract = 2,
    Multiplication = 3,
    Dividion = 4,
    mix = 5
};

struct stGameInfo
{
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short QuestionsNumber;
    short RightAnswers;
    short WrongAnswers;
    string LevelName;
    string OpTypeName;
};

short HowManyQuestions()
{
    short Number = 1;
    do
    {
        cout << "How Many Questions Do You Want To Answer? from 1 to 100? ";
        cin >> Number;
    } while (Number < 1 || Number > 100);

    return Number;
}

enQuestionLevel ReadQuestionsLevel()
{
    short Level = 1;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return (enQuestionLevel)Level;
}

enOperationType ReadOperationType()
{
    short OperationType = 1;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);

    return (enOperationType)OperationType;
}

int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

string LevelName(enQuestionLevel Level)
{
    switch (Level)
    {
    case enQuestionLevel::Easy:
        return "Easy";
    case enQuestionLevel::Med:
        return "Med";
    case enQuestionLevel::Hard:
        return "Hard";
    case enQuestionLevel::Mix:
        return "Mix";
    }
    return "";
}

string OperationName(enOperationType OpType)
{
    string OpTypes[5] = {"+", "-", "*", "/", "Mix"};

    return OpTypes[(int)OpType - 1];
}

short GetNumber(enQuestionLevel Level)
{
    switch (Level)
    {
    case enQuestionLevel::Easy:
        return RandomNumber(1, 10);
    case enQuestionLevel::Med:
        return RandomNumber(10, 50);
    case enQuestionLevel::Hard:
        return RandomNumber(50, 100);
    case enQuestionLevel::Mix:
        return RandomNumber(1, 100);
    }
    return RandomNumber(1, 100);
}

enOperationType RandomOpType()
{
    return (enOperationType)RandomNumber(1, 4);
}

int CalculateOperation(short Number1, short Number2, enQuestionLevel Level, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Addition:
        return Number1 + Number2;
    case enOperationType::Subtract:
        return Number1 - Number2;
    case enOperationType::Multiplication:
        return Number1 * Number2;
    case enOperationType::Dividion:
        return Number1 / Number2;
    }
    return 0;
}

void PlayGame(stGameInfo &GameInfo)
{
    GameInfo.QuestionsNumber = HowManyQuestions();
    GameInfo.QuestionLevel = ReadQuestionsLevel();
    GameInfo.OperationType = ReadOperationType();
    GameInfo.LevelName = LevelName(GameInfo.QuestionLevel);
    GameInfo.OpTypeName = OperationName(GameInfo.OperationType);
    GameInfo.RightAnswers = 0, GameInfo.WrongAnswers = 0;

    short Number1, Number2;
    int UserAnswer, RightAnswer;

    for (int i = 1; i <= GameInfo.QuestionsNumber; i++)
    {
        Number1 = GetNumber(GameInfo.QuestionLevel);
        Number2 = GetNumber(GameInfo.QuestionLevel);
        enOperationType RandOpType = (enOperationType)RandomOpType();

        if (GameInfo.OperationType == enOperationType::mix)
        {
            RightAnswer = CalculateOperation(Number1, Number2, GameInfo.QuestionLevel, RandOpType);
        }
        else
        {
            RightAnswer = CalculateOperation(Number1, Number2, GameInfo.QuestionLevel, GameInfo.OperationType);
        }

        cout << "\n\nQuestion [" << i << "/" << GameInfo.QuestionsNumber << "]\n\n";
        cout << Number1 << endl;
        if (GameInfo.OperationType == enOperationType::mix)
            cout << Number2 << " " << OperationName(RandOpType) << endl;
        else
            cout << Number2 << " " << GameInfo.OpTypeName << endl;
        cout << "________________\n";
        cin >> UserAnswer;
        if (UserAnswer == RightAnswer)
        {
            cout << "Rigth Answer :-)" << endl;
            GameInfo.RightAnswers++;
            system("COLOR 2F");
        }
        else
        {
            cout << "Wrong Answer :-( " << endl;
            cout << "The Right Answer is: " << RightAnswer << endl;
            GameInfo.WrongAnswers++;
            system("COLOR 4F");
        }
    }
}

void PrintFailOrPass(stGameInfo GameInfo)
{
    if (GameInfo.RightAnswers >= GameInfo.WrongAnswers)
    {
        cout << "Pass :-)";
        system("COLOR 2F");
    }
    else
    {
        cout << "Fail :-(";
        system("COLOR 4F");
    }
}

void ResetScreen()
{
    system("cls");
    system("COLOR 0F");
}

void ShowFinalResult(stGameInfo GameInfo)
{
    cout << "\n__________________________________________________________\n";
    cout << "\n Final Result is ";
    PrintFailOrPass(GameInfo);
    cout << "\n__________________________________________________________\n";
    cout << "\nNumber of Questions: " << GameInfo.QuestionsNumber << endl;
    cout << "Questions Level      : " << GameInfo.LevelName << endl;
    cout << "Operation Type       : " << GameInfo.OpTypeName << endl;
    cout << "Number of Right Answers: " << GameInfo.RightAnswers << endl;
    cout << "Number of Wrong Answers: " << GameInfo.WrongAnswers << endl;
    cout << "__________________________________________________________\n";
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameInfo Game;
        PlayGame(Game);
        ShowFinalResult(Game);
        cout << "\nDo You Want To Play Again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}
