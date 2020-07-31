#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE
{
    AI_EASY = 1,
    AI_HARD
};

enum LiNE_NUMBER
{
    LN_H1,
    LN_H2,
    LN_H3,
    LN_H4,
    LN_H5,
    LN_V1,
    LN_V2,
    LN_V3,
    LN_V4,
    LN_V5,
    LN_LTD,
    LN_RTD
};

void SetNumber(int *pArray)
{
    for (int i = 0; i < 25; i++)
    {
        pArray[i] = i + 1;
    }
}

void ShuffleNumber(int *pArray)
{
    int iTemp, idx1, idx2;

    for (int i = 0; i < 100; i++)
    {
        idx1 = rand() % 25;
        idx2 = rand() % 25;

        iTemp = pArray[idx1];
        pArray[idx1] = pArray[idx2];
        pArray[idx2] = iTemp;
    }
}

AI_MODE SelectMode()
{
    int iAIMode;

    // AI 난이도 선택

    while (true)
    {
        system("cls");
        cout << "1. Easy" << endl;
        cout << "2. Hard" << endl;
        cout << "AI 모드를 선택하시오. : ";
        cin >> iAIMode;

        if (iAIMode >= AI_EASY && iAIMode <= AI_HARD)
            break;
    }

    return (AI_MODE)iAIMode;
}

void OutPutBingoPan(int *pArray, int iBingo)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (pArray[i * 5 + j] == INT_MAX)
                cout << "*\t";

            else
                cout << pArray[i * 5 + j] << "\t";
        }
        cout << endl;
    }

    cout << "Bingo Line : " << iBingo << endl
         << endl;
}

bool ChangeNumber(int *pArray, int iInput)
{
    bool bAcc = true;

    for (int i = 0; i < 25; i++)
    {
        if (iInput == pArray[i])
        {
            bAcc = false;

            pArray[i] = INT_MAX;

            return bAcc;
        }
    }

    // 여기까지 오게 되면  같은 숫자가 없다는 것
    // 즉, 중복된 숫자를 입력했기 때문에 true를 리턴
    return true;
}

int SelectAINumber(int *pArrary, AI_MODE Emode)
{
    // 선택안된 목록 배열을 만들어준다.
    int iNoneSelect[25] = {};

    // 선택안된 숫자 갯수를 정한다.
    int iNoneSelectCount = 0;

    // AI 모드 선택

    switch (Emode)
    {
    /*
	Easy 모드는 선택안된 숫자 목록을 만들어서 그 목록중 하나를 선택하게 한다. (랜덤)
	*/
    case AI_EASY:
        // 선택안된 숫자목록을 만들어준다.
        // 선택안된 숫자 갯수는 목록을 만들때 카운팅해준다.

        iNoneSelectCount = 0;
        for (int i = 0; i < 25; i++)
        {
            // 현재 숫자가 *이 아닐 경우
            if (pArrary[i] != INT_MAX)
            {
                // *이 아닐 경우 iNoneSelectCount 를 인덱스로 활용 한다.
                // 선택 안된 목록에 추가할때마다 개수를 1개씩 증가
                // 시켜서 총 선택안된 갯수를 구해준다.
                // but 0부터 카운트가 시작되므로 0번에 넣고, ++ 해서 1개
                // 추가되었다라고 해준다.
                iNoneSelect[iNoneSelectCount] = pArrary[i];
                ++iNoneSelectCount;
            }
        }

        // for 문이 빠져 나오게되면 선택안된 숫자 목록이 만들어지고
        // 선택안된 목록의 갯수가 만들어지게된다.
        // 선택안된 목록중 랜덤으로 하나를 얻어오도록 인덱스를 랜덤하게 구해준다.

        return iNoneSelect[rand() % iNoneSelectCount];

    case AI_HARD:
        /*
		하드모드는 현재 숫자중 빙고줄 완성 가능성이 가장 높은 줄을
		찾아서 그 줄에 있는 숫자중 하나를 *로 만들어준다.
		*/
        int iLine;
        int iStarCount = 0;
        int iSaveCount = 0;

        // 가로 라인 중 가장 *이 많은 라인을 찾아낸다.
        for (int i = 0; i < 5; i++)
        {
            iStarCount = 0;
            for (int j = 0; j < 5; j++)
            {
                if (pArrary[i * 5 + j] == INT_MAX)
                    ++iStarCount;
            }

            // 별이 5개 미만이여야 빙고 줄이 아니고 기존에 가장 많은
            // 라인의 별보다 커야 가장 별이 많은 라인이므로 라인을
            // 교체해주고 저장된 별 수를 교체한다.
            if (iStarCount < 5 && iStarCount > iSaveCount)
            {
                // 가로라인은  0 ~ 4 로 의미 부여했다.
                // 가로 라인 중 가장 별이 많은 라인이다.
                iLine = i;
                iSaveCount = iStarCount;
            }
        }

        // 가로 라인중 가장 별이 많은 라인을 구했다.
        // 이 값과 세로 라인들을 비교하여 별이 가장 많은 라인을 구한다.
        for (int i = 0; i < 5; i++)
        {
            iStarCount = 0;
            for (int j = 0; j < 5; j++)
            {
                if (pArrary[j * 5 + i] == INT_MAX)
                    ++iStarCount;
            }

            if (iStarCount < 5 && iStarCount > iSaveCount)
            {
                // 세로 라인중 가장 별이 많은 라인을 구했다.
                // 세로라인은 5 ~ 9 로 의미를 부여함.
                iLine = i + 5;
                iSaveCount = iStarCount;
            }
        }

        // 왼쪽 상단 - > 오른쪽 하단 대각선 체크
        for (int i = 0; i < 25; i += 6)
        {
            if (pArrary[i] == INT_MAX)
            {
                ++iStarCount;
            }

            if (iStarCount < 5 && iStarCount > iSaveCount)
            {
                // 왼쪽 - > 오른쪽 대각선이 가장 별이 많은 라인이다면.
                // 왼쪽 - > 오른쪽 대각선은 10 으로 의미를 부여함.
                iLine = LN_LTD;
                iSaveCount = iStarCount;
            }
        }

        // 오른쪽 상단 - > 왼쪽 하단 대각선 체크
        for (int i = 5; i < 25; i += 4)
        {
            if (pArrary[i] == INT_MAX)
            {
                ++iStarCount;
            }

            if (iStarCount < 5 && iStarCount > iSaveCount)
            {
                // 오른쪽 - > 왼쪽 대각선이 가장 별이 많은 라인이다면.
                // 오른쪽 - > 왼쪽 대각선은 11 으로 의미를 부여함.
                iLine = LN_RTD;
                iSaveCount = iStarCount;
            }
        }

        // 모든 라인을 조사했으면 iLine에 가능성이 가장 높은 줄 번호가 저장됨
        // 그 줄에 있는 *이 아닌 숫자중 하나를 선택하면 된다.

        // 가로줄일 경우  0 ~ 4 사이의 값이다.
        if (iLine <= LN_H5)
        {
            for (int i = 0; i < 5; i++)
            {
                // 현재 줄에서 *이 아닌 숫자를 찾아낸다.
                if (pArrary[iLine * 5 + i] != INT_MAX)
                {
                    return pArrary[iLine * 5 + i];
                }
            }
        }

        //세로줄일 경우  5 ~ 9 사이의 값이다.
        if (iLine <= LN_V5)
        {
            for (int i = 0; i < 5; i++)
            {
                if (pArrary[i * 5 + (iLine - 5)] != INT_MAX)
                {
                    return pArrary[i * 5 + (iLine - 5)];
                }
            }
        }

        // 왼쪽 - > 오른쪽 대각선일 경우  10의 값이다.
        if (iLine == LN_LTD)
        {
            for (int i = 0; i < 25; i += 6)
            {
                if (pArrary[i] != INT_MAX)
                {
                    return pArrary[i];
                }
            }
        }

        // 오른쪽 - > 왼쪽 대각선일 경우  11의 값이다.
        if (iLine == LN_RTD)
        {
            for (int i = 4; i < 25; i += 4)
            {
                if (pArrary[i] != INT_MAX)
                {
                    return pArrary[i];
                }
            }
        }

        break;
    }

    return -1;
}

int BingoCountingH(int *pArray)
{
    int iStar = 0, iBingo = 0;

    for (int i = 0; i < 5; i++)
    {
        iStar = 0;

        for (int j = 0; j < 5; j++)
        {
            if (pArray[i * 5 + j] == INT_MAX)
                ++iStar;
        }

        if (iStar == 5)
            ++iBingo;
    }

    return iBingo;
}

int BingoCountingV(int *pArray)
{
    int iStar = 0, iBingo = 0;

    for (int i = 0; i < 5; i++)
    {
        iStar = 0;

        for (int j = 0; j < 5; j++)
        {
            if (pArray[j * 5 + i] == INT_MAX)
                ++iStar;
        }

        if (iStar == 5)
            ++iBingo;
    }

    return iBingo;
}

int BingoCountingLTD(int *pArray)
{
    int iStar = 0, iBingo = 0;

    for (int i = 0; i < 25; i += 6)
    {
        if (pArray[i] == INT_MAX)
            ++iStar;
    }

    if (iStar == 5)
        ++iBingo;

    return iBingo;
}

int BingoCountingRTD(int *pArray)
{
    int iStar = 0, iBingo = 0;

    for (int i = 4; i < 25; i += 4)
    {
        if (pArray[i] == INT_MAX)
            ++iStar;
    }

    if (iStar == 5)
        ++iBingo;

    return iBingo;
}

int BingoCounting(int *pArray)
{
    int iBingo = 0;

    // 가로줄 체크
    iBingo += BingoCountingH(pArray);

    // 세로줄 체크
    iBingo += BingoCountingV(pArray);

    // 왼쪽상단 - > 오른쪽 하단 대각선 체크
    iBingo += BingoCountingLTD(pArray);

    // 오른쪽상단 -> 왼쪽 하단 대각선 체크
    iBingo += BingoCountingRTD(pArray);

    return iBingo;
}

int main()
{
    srand((unsigned int)time(0));

    // 빙고 판을 만든다.

    int iNumber[25] = {};
    int iAINumber[25] = {};

    SetNumber(iNumber);
    SetNumber(iAINumber);

    // 빙고 판을 섞어준다.

    ShuffleNumber(iNumber);
    ShuffleNumber(iAINumber);

    int iBingo = 0, iAiBingo = 0;

    // AI 모드 선택
    AI_MODE eAIMode = SelectMode();

    while (true)
    {
        system("cls");

        cout << "============================= Player =============================" << endl;

        // Player 빙고판 출력

        OutPutBingoPan(iNumber, iBingo);

        cout << "============================= AI =============================" << endl
             << endl;

        // AI 모드 출력
        switch (eAIMode)
        {
        case AI_EASY:
            cout << "AIMode : Easy" << endl
                 << endl;
            break;
        case AI_HARD:
            cout << "AIMode : Hard" << endl
                 << endl;
            break;
        }

        // AI 빙고판 출력
        OutPutBingoPan(iAINumber, iAiBingo);

        // Bingo가 5개가 되면 승리
        if (iBingo >= 5)
        {
            cout << "Player 승리" << endl;
            break;
        }

        else if (iAiBingo >= 5)
        {
            cout << "AI 승리" << endl;
            break;
        }

        cout << "숫자를 입력하세요( 0 : 종료) : ";
        int iInput;
        cin >> iInput;

        if (iInput == 0)
            break;
        else if (iInput < 0 || iInput > 25)
            continue;

        bool bAcc = ChangeNumber(iNumber, iInput);

        // bAcc 가  true 일 경우 중복된 숫자를 입력해서 숫자를  * 로
        // 바꾸지 못했으므로 다시 입력받게 continue 해준다.
        if (bAcc)
            continue;

        // 중복이 아니라면 AI 숫자도 찾아서 *로 바꿔준다.
        else
            ChangeNumber(iAINumber, iInput);

        // AI가 숫자를 선택한다. AI 모드에 맞춰서 선택되도록 함
        iInput = SelectAINumber(iAINumber, eAIMode);

        // player 와 , Ai 의 숫자를 *로 바꿔준다.

        ChangeNumber(iNumber, iInput);

        ChangeNumber(iAINumber, iInput);

        // 빙고 줄 수를 체크하는것은 매번 숫자를 입력할때마다 처음부터
        // 새로 카운트를 할것이다. 그러므로 iBingo 변수를 0으로 매번
        // 초기화하고 새롭게 줄 수를 구해주도록 한다.
        iBingo = BingoCounting(iNumber);
        iAiBingo = BingoCounting(iAINumber);
    }

    return 0;
}