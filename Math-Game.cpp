#include <iostream>
#include <ctime>

using namespace std;

enum enQuestionsLevel
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

string GetQuestionSympol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Addition:
        return "+";
        break;
    case enOperationType::Subtract:
        return "-";
        break;
    case enOperationType::Multiplication:
        return "*";
        break;
    case enOperationType::Dividion:
        return "/";
        break;

    default:
        return "Mix";
        break;
    }
}

string GetQuestionLevelText(enQuestionsLevel Level)
{
    string Levels[4] = {"Easy", "Med", "Hard", "Mix"};
    return Levels[(int)Level - 1];
}

int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

void ColorScreen(bool pass)
{
    if (pass)
    {
        system("COLOR 2F");
    }
    else
    {
        system("COLOR 4F");
        cout << "\a";
    }
}

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

enQuestionsLevel ReadQuestionsLevel()
{
    short Level = 1;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return (enQuestionsLevel)Level;
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

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
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
    return Number1 + Number2;
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateOneQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::mix)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
        break;
    case enQuestionsLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
        break;
    case enQuestionsLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
        break;
    }

    return Question;
}

void GeneratesQuestions(stQuizz &Quizz)
{
    for (int Quesion = 0; Quesion < Quizz.NumberOfQuestion; Quesion++)
    {
        Quizz.QuestionList[Quesion] = GenerateOneQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;

    return Answer;
}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " " << GetQuestionSympol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << "\n________________\n";
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    ColorScreen(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz &Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
    {
        PrintTheQuestion(Quizz, Question);

        Quizz.QuestionList[Question].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, Question);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool pass)
{
    if (pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
    cout << "\n";
    cout << "_________________________________________\n\n";
    cout << "Final Results is: " << GetFinalResultText(Quizz.isPass);
    cout << "\n_________________________________________\n\n";
    cout << "Number Of Questions: " << Quizz.NumberOfQuestion << endl;
    cout << "Question Level     : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "Operatio Type      : " << GetQuestionSympol(Quizz.OpType) << endl;
    cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "_________________________________________\n";
}

void PlayGame()
{

    stQuizz Quizz;

    Quizz.NumberOfQuestion = HowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOperationType();

    GeneratesQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResult(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("COLOR 0F");
}

void StartGame()
{

    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayGame();

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

