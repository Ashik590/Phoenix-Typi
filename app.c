/* --- Game Documentation

    1. It will generate easy text paragraph based on the first 20 words of the word file. There are 20 easy words (Length of 1-4, Syllable 1-2) in the first 20 line of the "word.txt" file

    2. It will generate medium text paragraph based on the next 40 words of the word file. There are 40 medium words (Length of 5-7, Syllable 2-3) in the next 40 line of the "word.txt" file

    3. It will generate hard text paragraph based on the last 60 words of the word file. There are 60 hard words (Length of 10+, Syllable 3+) in the last 60 line of the "word.txt" file

    4. Please, run this game in full screen terminal

    5. Compile by the command 'gcc app.c -o app.out -lncurses' and run by the command './app.out < word.txt'

   --- Game Documentation ---*/

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// Animation Func that will repeatedly animate a single char
void animativeText(char ch, int size, WINDOW *win, int speed)
{
    for (int i = 0; i < size; i++)
    {
        usleep(speed + i * i);
        wprintw(win, "%c", ch);
        wrefresh(win);
    }
}

// That will animate a full text
void customAnimativeText(char *text, WINDOW *win, int speed)
{
    if (win)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            usleep(speed + i * i);
            wprintw(win, "%c", text[i]);
            wrefresh(win);
        }
    }
    else
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            usleep(speed + i * i);
            printw("%c", text[i]);
            refresh();
        }
    }
}

// generating random sample text
char easyWords[20][20];
char mediumWords[40][20];
char hardWords[60][20];
char generatedTextWords[60][20];
char generatedText[1000] = "";

void generatingText(int size)
{
    for (int i = 0; i < size; i++)
    {
        int r = rand() % size;

        if (size == 20 /*Easy mode*/)
            strcpy(generatedTextWords[i], easyWords[r]);
        else if (size == 40 /*medium mode*/)
            strcpy(generatedTextWords[i], mediumWords[r]);
        else if (size == 60 /*hard mode*/)
            strcpy(generatedTextWords[i], hardWords[r]);

        strcat(generatedText, generatedTextWords[i]);
        if (i != size - 1)
            strcat(generatedText, " ");
    }
}

// Printing a credit text

void printingCreditText(int terHeight, int terWidth, int isAnimative)
{
    char *creditText = "Developed By Azizul Hakim\n";
    move(terHeight - 2, (terWidth - 25) / 2);
    attron(A_DIM);
    if (isAnimative)
        customAnimativeText(creditText, NULL, 23000);
    else
        printw("%s", creditText);

    attroff(A_DIM);
}

int main()
{
    srand(time(NULL));

    // Getting words by redirecting input

    for (int i = 0; i < 20; i++)
    {
        scanf("%s", easyWords[i]);
    }
    for (int i = 0; i < 40; i++)
    {
        scanf("%s", mediumWords[i]);
    }
    for (int i = 0; i < 60; i++)
    {
        scanf("%s", hardWords[i]);
    }

    // Restore stdin to keyboard input (Very Important block of code)
    fclose(stdin);
    stdin = fopen("/dev/tty", "r");
    if (stdin == NULL)
    {
        perror("Failed to restore stdin");
        return 1;
    }

    initscr();
    cbreak();

    while (1)
    {
        // First Page of the game - Welcome

        strcpy(generatedText, "");

        // Getting Terminal Size
        int terHeight, terWidth;
        getmaxyx(stdscr, terHeight, terWidth);

        start_color();

        // Defining color pairs
        init_pair(1, COLOR_MAGENTA /*Text color*/, COLOR_BLACK /*Bg color*/);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        init_pair(7, COLOR_BLACK, COLOR_WHITE);

        // Making the cursor invisible
        curs_set(0);

        // Making a welcome window
        int welcomeWinWidth = 42;
        int welcomeWinHeight = 3;

        // Setting it into the middle of the screen
        int welcomeWinX = (terWidth - welcomeWinWidth) / 2;
        int welcomeWinY = (terHeight - welcomeWinHeight) / 2;
        WINDOW *welcomeWin = newwin(welcomeWinHeight, welcomeWinWidth, welcomeWinY, welcomeWinX);

        // After every creation of a WINDOW, we need to refresh the screen
        refresh();

        // Making the texts inside the Welcome Window with color-pair-1
        wattron(welcomeWin, COLOR_PAIR(1));
        animativeText('=', 41, welcomeWin, 10000);
        wattron(welcomeWin, A_BOLD);
        wprintw(welcomeWin, "\n");
        animativeText('<', 7, welcomeWin, 10000);
        wattroff(welcomeWin, COLOR_PAIR(1));

        wattron(welcomeWin, COLOR_PAIR(2));
        char *welcomeNote = "  WELCOME TO PHOENIX TYPI  ";
        customAnimativeText(welcomeNote, welcomeWin, 10000);
        wattroff(welcomeWin, COLOR_PAIR(2));
        wattron(welcomeWin, COLOR_PAIR(1));
        animativeText('>', 7, welcomeWin, 10000);

        wprintw(welcomeWin, "\n");
        wattroff(welcomeWin, A_BOLD);
        animativeText('=', 41, welcomeWin, 10000);
        wattroff(welcomeWin, COLOR_PAIR(1));

        // Adding a credit text in the bottom with A_DIM text format
        printingCreditText(terHeight, terWidth, 1);

        // The tap text width is 39. Putted in middle just after the welcome window with a blinking format
        char *tapText = "Tap any button to jump into the action!";
        move(welcomeWinY + 4, (terWidth - 39) / 2);
        usleep(300000);
        attron(A_BLINK);
        printw("Tap any button to jump into the action!");
        attroff(A_BLINK);
        timeout(0);
        char ch_;
        while (1)
        {
            ch_ = getch();
            if (ch_ != ERR)
            {
                break;
            }
        }

        // Second Page of the game - Mode selection
        werase(welcomeWin);
        wrefresh(welcomeWin); // It is required to refresh the window after erasing itself
        clear();
        refresh();

        // Creating a title for all page

        move(1, (terWidth - 27 /*Text size*/) / 2);
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("PHOENIX TYPI - A TYPE METER");
        move(2, (terWidth - 33) / 2);
        printw("_________________________________");
        attroff(COLOR_PAIR(1) | A_BOLD);
        refresh();

        // Credit text again
        printingCreditText(terHeight, terWidth, 0);

        // Creating a menu in a middle of the page
        int heightMode = 12;
        int widthMode = 54;
        WINDOW *modeWin = newwin(heightMode, widthMode, (terHeight - heightMode) / 2, (terWidth - widthMode) / 2);
        refresh();

        wattron(modeWin, A_BOLD);
        wprintw(modeWin, "SELECT YOUR GAME MODE\n");
        wattroff(modeWin, A_BOLD);
        wmove(modeWin, 3, 0);
        wattron(modeWin, COLOR_PAIR(7));
        wprintw(modeWin, "[1] Easy    \n\n");
        wattroff(modeWin, COLOR_PAIR(7));

        wprintw(modeWin, "[2] Medium  \n\n");
        wprintw(modeWin, "[3] Hard    \n\n\n\n\n");
        wattron(modeWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
        wprintw(modeWin, "Press [Tab] to switch modes | Press [Enter] to proceed");
        wattroff(modeWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
        wrefresh(modeWin);

        curs_set(0); // Making the cursor visible

        noecho();

        char mode_char;
        int mode = 1;
        while (1)
        {
            mode_char = getch();
            if (mode_char == '\t' | mode_char == 9)
            {
                mode++;
                if (mode > 3)
                {
                    mode = 1;
                }
                else if (mode < 1)
                {
                    mode = 3;
                }

                wmove(modeWin, 3, 0);
                if (mode == 1)
                {
                    wattron(modeWin, COLOR_PAIR(7));
                    wprintw(modeWin, "[1] Easy    \n\n");
                    wattroff(modeWin, COLOR_PAIR(7));

                    wprintw(modeWin, "[2] Medium  \n\n");
                    wprintw(modeWin, "[3] Hard    \n\n\n\n\n");
                }
                else if (mode == 2)
                {
                    wprintw(modeWin, "[1] Easy    \n\n");

                    wattron(modeWin, COLOR_PAIR(7));
                    wprintw(modeWin, "[2] Medium  \n\n");
                    wattroff(modeWin, COLOR_PAIR(7));

                    wprintw(modeWin, "[3] Hard    \n\n\n\n\n");
                }
                else
                {
                    wprintw(modeWin, "[1] Easy    \n\n");
                    wprintw(modeWin, "[2] Medium  \n\n");

                    wattron(modeWin, COLOR_PAIR(7));
                    wprintw(modeWin, "[3] Hard    \n\n\n\n\n");
                    wattroff(modeWin, COLOR_PAIR(7));
                }
                wattron(modeWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
                wprintw(modeWin, "Press [Tab] to switch modes | Press [Enter] to proceed");
                wattroff(modeWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
                wrefresh(modeWin);
            }
            else if (mode_char == KEY_ENTER | mode_char == '\n' | mode_char == KEY_ENTER)
            {
                break;
            }
        }

        // Third page of the game
        werase(modeWin);
        wrefresh(modeWin);
        refresh();

        // Making time Option window - get to know the gaming time period
        int heightTimeOpt = 14;
        int widthTimeOpt = 54;
        WINDOW *timeOptWin = newwin(heightTimeOpt, widthTimeOpt, (terHeight - heightTimeOpt) / 2, (terWidth - widthMode) / 2);
        refresh();

        wattron(timeOptWin, A_BOLD);
        wprintw(timeOptWin, "SET YOUR TIME LIMIT\n");
        wattroff(timeOptWin, A_BOLD);
        wmove(timeOptWin, 3, 0);
        wattron(timeOptWin, COLOR_PAIR(7));
        wprintw(timeOptWin, "[1] 15 seconds   \n\n");
        wattroff(timeOptWin, COLOR_PAIR(7));

        wprintw(timeOptWin, "[2] 30 seconds   \n\n");
        wprintw(timeOptWin, "[3] 45 seconds   \n\n");
        wprintw(timeOptWin, "[4] 60 seconds   \n\n\n\n\n");
        wattron(timeOptWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
        wprintw(timeOptWin, "Press [Tab] to switch options | Press [Enter] to proceed");
        wattroff(timeOptWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
        wrefresh(timeOptWin);

        char timeOptCh;
        int timePeriod = 15; // Time to count down
        int timeOptSwitch = 1;

        while (1)
        {
            timeOptCh = getch();
            if (timeOptCh == '\t' | timeOptCh == 9)
            {
                timeOptSwitch++;
                if (timeOptSwitch > 4)
                {
                    timeOptSwitch = 1;
                }
                else if (timeOptSwitch < 1)
                {
                    timeOptSwitch = 4;
                }

                wmove(timeOptWin, 3, 0);
                if (timeOptSwitch == 1)
                {
                    timePeriod = 15;
                    wattron(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[1] 15 seconds   \n\n");
                    wattroff(timeOptWin, COLOR_PAIR(7));

                    wprintw(timeOptWin, "[2] 30 seconds   \n\n");
                    wprintw(timeOptWin, "[3] 45 seconds   \n\n");
                    wprintw(timeOptWin, "[4] 60 seconds   \n\n\n\n\n");
                }
                else if (timeOptSwitch == 2)
                {
                    timePeriod = 30;
                    wprintw(timeOptWin, "[1] 15 seconds   \n\n");

                    wattron(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[2] 30 seconds   \n\n");
                    wattroff(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[3] 45 seconds   \n\n");
                    wprintw(timeOptWin, "[4] 60 seconds   \n\n\n\n\n");
                }
                else if (timeOptSwitch == 3)
                {
                    timePeriod = 45;
                    wprintw(timeOptWin, "[1] 15 seconds   \n\n");

                    wprintw(timeOptWin, "[2] 30 seconds   \n\n");
                    wattron(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[3] 45 seconds   \n\n");
                    wattroff(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[4] 60 seconds   \n\n\n\n\n");
                }
                else
                {
                    timePeriod = 60;
                    wprintw(timeOptWin, "[1] 15 seconds   \n\n");

                    wprintw(timeOptWin, "[2] 30 seconds   \n\n");
                    wprintw(timeOptWin, "[3] 45 seconds   \n\n");
                    wattron(timeOptWin, COLOR_PAIR(7));
                    wprintw(timeOptWin, "[4] 60 seconds   \n\n\n\n\n");
                    wattroff(timeOptWin, COLOR_PAIR(7));
                }
                wattron(timeOptWin, A_DIM | A_ITALIC | COLOR_PAIR(1));
                wprintw(timeOptWin, "Press [Tab] to switch options | Press [Enter] to proceed");
                wattroff(timeOptWin, A_DIM | A_ITALIC | COLOR_PAIR(1));

                wrefresh(timeOptWin);
            }
            else if (timeOptCh == KEY_ENTER | timeOptCh == '\n' | timeOptCh == KEY_ENTER)
            {
                break;
            }
        }
        werase(timeOptWin);
        wrefresh(timeOptWin);

        // Forth page

        // Actual Part of the game

        move(3, 1);

        int challangeY; // Challange Window Y position

        // Displaying the mode
        printw("MODE : ");
        attron(A_BOLD);
        if (mode == 1)
        {
            attron(COLOR_PAIR(3));
            printw("EASY\n");
            attroff(COLOR_PAIR(3));

            generatingText(20);
            challangeY = 9;
        }
        else if (mode == 2)
        {
            attron(COLOR_PAIR(5));
            printw("MEDIUM\n");
            attroff(COLOR_PAIR(5));

            generatingText(40);
            challangeY = 10;
        }
        else if (mode == 3)
        {
            attron(COLOR_PAIR(4));
            printw("HARD\n");
            attroff(COLOR_PAIR(4));

            generatingText(60);
            challangeY = 13;
        }
        attroff(A_BOLD);

        // Making the sample text presentation window
        int heightgeneratedTextWin = 10;
        WINDOW *generatedTextWin = newwin(heightgeneratedTextWin, terWidth - 2, 5, 1);
        refresh();
        wattron(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
        wmove(generatedTextWin, 0, 0);
        wprintw(generatedTextWin, "%s", generatedText);
        wattroff(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
        wrefresh(generatedTextWin);

        // Short notice like Challange

        WINDOW *challange = newwin(3, 64 + 6, challangeY, (terWidth - 64 - 4) / 2);
        wattron(challange, COLOR_PAIR(1) | A_BOLD);
        box(challange, 0, 0);
        wattroff(challange, COLOR_PAIR(1) | A_BOLD);
        refresh();
        wmove(challange, 1, 2);
        wattron(challange, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
        wprintw(challange, " TYPE THE TEXT BELOW, AND LET'S SEE HOW FAST AND ACCURATE YOU ARE ");
        wattroff(challange, COLOR_PAIR(1) | A_BOLD | A_STANDOUT);
        wrefresh(challange);

        // Time Notice
        mvprintw(3, terWidth - 18, "TIME : ");
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(3, terWidth - 11, "%d SECONDS", timePeriod);
        attroff(COLOR_PAIR(4) | A_BOLD);

        // Counting Time
        time_t start = time(NULL);
        time_t end;

        // Wrong character pressed notice
        char *wrongText = "Wrong character!";
        WINDOW *wrongCharWin = newwin(3, strlen(wrongText) + 6, terHeight - 3, terWidth - strlen(wrongText) - 6);

        wattron(wrongCharWin, COLOR_PAIR(4));
        box(wrongCharWin, 0, 0); // Making it visible
        wattroff(wrongCharWin, COLOR_PAIR(4));
        refresh();
        wmove(wrongCharWin, 1, 2);
        wattron(wrongCharWin, COLOR_PAIR(4) | A_BOLD | A_STANDOUT);
        wprintw(wrongCharWin, "%s", wrongText);
        wattroff(wrongCharWin, COLOR_PAIR(4) | A_BOLD | A_STANDOUT);
        wrefresh(wrongCharWin);

        werase(wrongCharWin); // Making it invisible
        wrefresh(wrongCharWin);

        // Making the typing portion
        move(challangeY + 3, 1);
        attron(A_DIM);
        printw("=> ");
        attroff(A_DIM);

        int userInputY = challangeY + 4;
        move(userInputY, 0);

        char userText[1000]; // Total Text that User typed
        userText[0] = '\0';
        int userTextInd = 0;

        int ind = 0;         // Sample Text Index
        int posX = 1;        // Cursor current position
        int sampleCharY = 0; // sample text focused character y position
        int sampleCharX = 0; // sample text focused character x position

        bool earlySubmission = 0;

        while (1)
        {
            /*-- Updating the time starts --*/
            timeout(1000);
            char ch = getch();
            end = time(NULL);

            attron(COLOR_PAIR(4) | A_BOLD);
            if (timePeriod - end + start < 0)
            {
                break;
            }
            else if (timePeriod - end + start < 10)
            {
                mvprintw(3, terWidth - 11, "0%ld", timePeriod - end + start);
            }
            else
            {
                mvprintw(3, terWidth - 11, "%ld", timePeriod - end + start);
            }
            attroff(COLOR_PAIR(4) | A_BOLD);

            /*-- Updating the time ends --*/

            int oneLineTotalChar = 0;
            if ((ch == 127 || ch == KEY_BACKSPACE) && ind > 0)
            {
                userTextInd--;
                userText[userTextInd] = '\0'; // Deleting the char from userText

                // Making the Wrong Char window invisible
                werase(wrongCharWin);
                wrefresh(wrongCharWin);

                ind--;
                posX--;
                if (posX < 1)
                {
                    posX = terWidth - 2;
                    userInputY--;
                }
                move(userInputY, posX);
                refresh();

                printw(" ");
                move(userInputY, posX);

                // Unfocusing the sample text current char
                sampleCharX--;
                if (sampleCharX < 0)
                {
                    sampleCharX = terWidth - 3;
                    sampleCharY--;
                }

                wattron(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
                wmove(generatedTextWin, sampleCharY, sampleCharX);
                wprintw(generatedTextWin, "%c", generatedText[ind]);
                wattroff(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
                wrefresh(generatedTextWin);
            }
            else if ((ch == KEY_ENTER || ch == 10))
            {
                // Making the Wrong Char window invisible
                werase(wrongCharWin);
                wrefresh(wrongCharWin);

                earlySubmission = true;
                refresh();
                break;
            }
            else if (ch != ERR && ch >= 32 && ch <= 126)
            {
                userText[userTextInd] = ch; // Adding the char to userText
                userTextInd++;
                userText[userTextInd] = '\0';

                move(userInputY, posX);
                oneLineTotalChar++;
                posX++;
                ind++;
                if (posX > terWidth - 2)
                {
                    posX = 1;
                    userInputY++;
                }
                if (ch == generatedText[ind - 1])
                {
                    // Making the Wrong Char window invisible
                    werase(wrongCharWin);
                    wrefresh(wrongCharWin);

                    attron(COLOR_PAIR(3) | A_BOLD);
                    printw("%c", ch);
                    attroff(COLOR_PAIR(3) | A_BOLD);

                    // Focusing the sample text current char

                    wattron(generatedTextWin, COLOR_PAIR(2) | A_BOLD);
                    wmove(generatedTextWin, sampleCharY, sampleCharX);
                    wprintw(generatedTextWin, "%c", generatedText[ind - 1]);
                    wattroff(generatedTextWin, COLOR_PAIR(2) | A_BOLD);
                    wrefresh(generatedTextWin);
                }
                else
                {
                    /* --- Making the Wrong Char window visible starts --- */

                    wattron(wrongCharWin, COLOR_PAIR(4) | A_BOLD);
                    box(wrongCharWin, 0, 0);
                    refresh();
                    wmove(wrongCharWin, 1, 2);
                    wattron(wrongCharWin, A_STANDOUT);
                    wprintw(wrongCharWin, " %s ", wrongText);
                    wattroff(wrongCharWin, A_STANDOUT);
                    wattroff(wrongCharWin, COLOR_PAIR(4) | A_BOLD);
                    wrefresh(wrongCharWin);
                    /* --- Making the Wrong Char window visible ends --- */

                    attron(COLOR_PAIR(4) | A_BOLD);
                    printw("%c", ch);
                    attroff(COLOR_PAIR(4) | A_BOLD);

                    // Focusing the sample text current char

                    wattron(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
                    wmove(generatedTextWin, sampleCharY, sampleCharX);
                    wprintw(generatedTextWin, "%c", generatedText[ind - 1]);
                    wattroff(generatedTextWin, COLOR_PAIR(2) | A_BOLD | A_DIM);
                    wrefresh(generatedTextWin);
                }
                sampleCharX++;
                if (sampleCharX > terWidth - 3)
                {
                    sampleCharX = 0;
                    sampleCharY++;
                }
            }
            refresh();
        }
        // Making the Wrong Char window invisible
        werase(wrongCharWin);
        wrefresh(wrongCharWin);
        refresh();

        // After the timeout and the timeout window

        char *timeoutText = "TIME'S UP !";
        if (earlySubmission)
            timeoutText = "Good Job !";
        else
            timeoutText = "TIME'S UP !";

        int timeoutWinHeight = 5;
        int timeoutWinWidth = 45;

        WINDOW *timeoutWin = newwin(timeoutWinHeight, timeoutWinWidth, terHeight - terHeight / 3, (terWidth - timeoutWinWidth) / 2);
        refresh();
        wattron(timeoutWin, COLOR_PAIR(2) | A_BOLD);
        box(timeoutWin, 0, 0);
        wattroff(timeoutWin, COLOR_PAIR(2) | A_BOLD);
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(3, terWidth - 11, "00");
        attroff(COLOR_PAIR(4) | A_BOLD);
        refresh();
        wmove(timeoutWin, 1, (timeoutWinWidth - strlen(timeoutText)) / 2);

        wattron(timeoutWin, COLOR_PAIR(2) | A_BOLD);
        wprintw(timeoutWin, "%s", timeoutText);
        wattroff(timeoutWin, COLOR_PAIR(2) | A_BOLD);

        wmove(timeoutWin, 3, 2);
        wprintw(timeoutWin, "To Estimate your Performance, Press ENTER");
        wrefresh(timeoutWin);
        timeout(0); // to delete the previous timeout countdown

        char chs;

        while (chs = getch())
        {
            if (chs == 10 | chs == KEY_ENTER) // Waiting for ENTER press
            {
                break;
            }
        }

        // 4th Page of the Game - Measurements

        clear();

        // Creating a title for all page

        move(1, (terWidth - 27 /*Text size*/) / 2);
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("PHOENIX TYPI - A TYPE METER");
        move(2, (terWidth - 33) / 2);
        printw("_________________________________");
        attroff(COLOR_PAIR(1) | A_BOLD);
        refresh();

        // Calculation

        int charMistakes = 0;
        int wordMistakes = 0;
        char currentWord[20];
        int curWordInd = 0;
        char userWords[60][20];
        int totalWordTyped = 0;
        float wpm = 0, cpm = 0, accuracy = 0;
        int correctCharTyped = 0;
        long timeSpend = end - start - 1;

        // Checking if user typed text is empty
        if (userTextInd)
        {
            for (int i = 0; i < userTextInd; i++)
            {
                if (userText[i] != generatedText[i])
                {
                    charMistakes++;
                }

                if (userText[i] != ' ')
                {
                    currentWord[curWordInd] = userText[i];
                    curWordInd++;
                }
                else
                {
                    currentWord[curWordInd] = '\0';
                    strcpy(userWords[totalWordTyped], currentWord);
                    totalWordTyped++;
                    curWordInd = 0;
                    currentWord[curWordInd] = '\0';
                }
            }
            currentWord[curWordInd] = '\0';
            strcpy(userWords[totalWordTyped], currentWord);
            totalWordTyped++;

            for (int i = 0; i < totalWordTyped; i++)
            {
                if (strcmp(userWords[i], generatedTextWords[i]))
                    wordMistakes++;
            }

            wpm = ((float)totalWordTyped / (float)timeSpend) * 60.0;
            cpm = ((float)userTextInd / (float)timeSpend) * 60.0;
            accuracy = (((float)userTextInd - (float)charMistakes) / (float)userTextInd) * 100;
            correctCharTyped = userTextInd - charMistakes;
        }

        // First Measurement
        int firstColMeasureX = 5;

        int secWidth = 29;
        WINDOW *sec1 = newwin(3, secWidth, 6, firstColMeasureX);
        wattron(sec1, COLOR_PAIR(3));
        box(sec1, 0, 0);
        wattroff(sec1, COLOR_PAIR(3));
        refresh();
        wmove(sec1, 1, 2);
        wattron(sec1, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec1, "Total Character Typed");
        wattroff(sec1, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec1);

        WINDOW *sec1_ = newwin(3, secWidth, 6, firstColMeasureX + secWidth);
        wattron(sec1_, COLOR_PAIR(3));
        box(sec1_, 0, 0);
        wattroff(sec1_, COLOR_PAIR(3));
        refresh();
        wmove(sec1_, 1, 2);

        wprintw(sec1_, "%d", userTextInd);

        wrefresh(sec1_);

        // Second Measurement
        WINDOW *sec2 = newwin(3, secWidth, 9, firstColMeasureX);
        wattron(sec2, COLOR_PAIR(3));
        box(sec2, 0, 0);
        wattroff(sec2, COLOR_PAIR(3));
        refresh();
        wmove(sec2, 1, 2);
        wattron(sec2, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec2, "Correct Character Typed");
        wattroff(sec2, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec2);

        WINDOW *sec2_ = newwin(3, secWidth, 9, firstColMeasureX + secWidth);
        wattron(sec2_, COLOR_PAIR(3));
        box(sec2_, 0, 0);
        wattroff(sec2_, COLOR_PAIR(3));
        refresh();
        wmove(sec2_, 1, 2);

        wprintw(sec2_, "%d", correctCharTyped);

        wrefresh(sec2_);

        // Third Measurement
        WINDOW *sec3 = newwin(3, secWidth, 12, firstColMeasureX);
        wattron(sec3, COLOR_PAIR(3));
        box(sec3, 0, 0);
        wattroff(sec3, COLOR_PAIR(3));
        refresh();
        wmove(sec3, 1, 2);
        wattron(sec3, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec3, "Wrong Character Typed");
        wattroff(sec3, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec3);

        WINDOW *sec3_ = newwin(3, secWidth, 12, firstColMeasureX + secWidth);
        wattron(sec3_, COLOR_PAIR(3));
        box(sec3_, 0, 0);
        wattroff(sec3_, COLOR_PAIR(3));
        refresh();
        wmove(sec3_, 1, 2);

        wprintw(sec3_, "%d", charMistakes);

        wrefresh(sec3_);

        // Forth Measurement
        WINDOW *sec4 = newwin(3, secWidth, 15, firstColMeasureX);
        wattron(sec4, COLOR_PAIR(3));
        box(sec4, 0, 0);
        wattroff(sec4, COLOR_PAIR(3));
        refresh();
        wmove(sec4, 1, 2);
        wattron(sec4, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec4, "Total Word Typed");
        wattroff(sec4, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec4);

        WINDOW *sec4_ = newwin(3, secWidth, 15, firstColMeasureX + secWidth);
        wattron(sec4_, COLOR_PAIR(3));
        box(sec4_, 0, 0);
        wattroff(sec4_, COLOR_PAIR(3));
        refresh();
        wmove(sec4_, 1, 2);
        wprintw(sec4_, "%d", totalWordTyped);
        wrefresh(sec4_);

        // 5th Measurement
        WINDOW *sec5 = newwin(3, secWidth, 18, firstColMeasureX);
        wattron(sec5, COLOR_PAIR(3));
        box(sec5, 0, 0);
        wattroff(sec5, COLOR_PAIR(3));
        refresh();
        wmove(sec5, 1, 2);
        wattron(sec5, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec5, "Wrong Word Typed");
        wattroff(sec5, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec5);

        WINDOW *sec5_ = newwin(3, secWidth, 18, firstColMeasureX + secWidth);
        wattron(sec5_, COLOR_PAIR(3));
        box(sec5_, 0, 0);
        wattroff(sec5_, COLOR_PAIR(3));
        refresh();
        wmove(sec5_, 1, 2);
        wprintw(sec5_, "%d", wordMistakes);
        wrefresh(sec5_);

        // 6th Measurement
        WINDOW *sec6 = newwin(3, secWidth, 6, terWidth - secWidth * 2 - firstColMeasureX);
        wattron(sec6, COLOR_PAIR(3));
        box(sec6, 0, 0);
        wattroff(sec6, COLOR_PAIR(3));
        refresh();
        wmove(sec6, 1, 2);
        wattron(sec6, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec6, "Words per min(WPM)");
        wattroff(sec6, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec6);

        WINDOW *sec6_ = newwin(3, secWidth, 6, terWidth - secWidth - firstColMeasureX);
        wattron(sec6_, COLOR_PAIR(3));
        box(sec6_, 0, 0);
        wattroff(sec6_, COLOR_PAIR(3));
        refresh();
        wmove(sec6_, 1, 2);
        wprintw(sec6_, "%.2f", wpm);
        wrefresh(sec6_);

        // 7th Measurement
        WINDOW *sec7 = newwin(3, secWidth, 9, terWidth - secWidth * 2 - firstColMeasureX);
        wattron(sec7, COLOR_PAIR(3));
        box(sec7, 0, 0);
        wattroff(sec7, COLOR_PAIR(3));
        refresh();
        wmove(sec7, 1, 2);
        wattron(sec7, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec7, "Character per min(CPM)");
        wattroff(sec7, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec7);

        WINDOW *sec7_ = newwin(3, secWidth, 9, terWidth - secWidth - firstColMeasureX);
        wattron(sec7_, COLOR_PAIR(3));
        box(sec7_, 0, 0);
        wattroff(sec7_, COLOR_PAIR(3));
        refresh();
        wmove(sec7_, 1, 2);
        wprintw(sec7_, "%.2f", cpm);
        wrefresh(sec7_);

        // 8th Measurement
        WINDOW *sec8 = newwin(3, secWidth, 12, terWidth - secWidth * 2 - firstColMeasureX);
        wattron(sec8, COLOR_PAIR(3));
        box(sec8, 0, 0);
        wattroff(sec8, COLOR_PAIR(3));
        refresh();
        wmove(sec8, 1, 2);
        wattron(sec8, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec8, "Accuracy");
        wattroff(sec8, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec8);

        WINDOW *sec8_ = newwin(3, secWidth, 12, terWidth - secWidth - firstColMeasureX);
        wattron(sec8_, COLOR_PAIR(3));
        box(sec8_, 0, 0);
        wattroff(sec8_, COLOR_PAIR(3));
        refresh();
        wmove(sec8_, 1, 2);
        wprintw(sec8_, "%.2f%%", accuracy);
        wrefresh(sec8_);

        // 9th Measurement
        WINDOW *sec9 = newwin(3, secWidth, 15, terWidth - secWidth * 2 - firstColMeasureX);
        wattron(sec9, COLOR_PAIR(3));
        box(sec9, 0, 0);
        wattroff(sec9, COLOR_PAIR(3));
        refresh();
        wmove(sec9, 1, 2);
        wattron(sec9, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec9, "Elapsed Time");
        wattroff(sec9, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec9);

        WINDOW *sec9_ = newwin(3, secWidth, 15, terWidth - secWidth - firstColMeasureX);
        wattron(sec9_, COLOR_PAIR(3));
        box(sec9_, 0, 0);
        wattroff(sec9_, COLOR_PAIR(3));
        refresh();
        wmove(sec9_, 1, 2);
        wprintw(sec9_, "%ld seconds", timeSpend);
        wrefresh(sec9_);

        // 10th Measurement
        WINDOW *sec10 = newwin(3, secWidth, 18, terWidth - secWidth * 2 - firstColMeasureX);
        wattron(sec10, COLOR_PAIR(3));
        box(sec10, 0, 0);
        wattroff(sec10, COLOR_PAIR(3));
        refresh();
        wmove(sec10, 1, 2);
        wattron(sec10, COLOR_PAIR(3) | A_BOLD);
        wprintw(sec10, "Early Submission");
        wattroff(sec10, COLOR_PAIR(3) | A_BOLD);
        wrefresh(sec10);

        WINDOW *sec10_ = newwin(3, secWidth, 18, terWidth - secWidth - firstColMeasureX);
        wattron(sec10_, COLOR_PAIR(3));
        box(sec10_, 0, 0);
        wattroff(sec10_, COLOR_PAIR(3));
        refresh();
        wmove(sec10_, 1, 2);

        if (earlySubmission)
        {
            wattron(sec10_, COLOR_PAIR(4) | A_BOLD);
            wprintw(sec10_, "YES");
            wattroff(sec10_, COLOR_PAIR(4) | A_BOLD);
        }
        else
        {
            wattron(sec10_, COLOR_PAIR(2) | A_BOLD);
            wprintw(sec10_, "NO");
            wattroff(sec10_, COLOR_PAIR(2) | A_BOLD);
        }
        wrefresh(sec10_);

        // Headline of the measurement page
        move(4, 5);
        attron(COLOR_PAIR(3) | A_BOLD | A_STANDOUT);
        printw(" TYPING ANALYSIS ");
        attroff(COLOR_PAIR(3) | A_BOLD | A_STANDOUT);

        // Making user guideline
        move(terHeight - 5, (terWidth - 47) / 2);
        attron(A_DIM | A_ITALIC | COLOR_PAIR(1));
        printw("Press [Enter] to play again | Press [q] to exit");
        attroff(A_DIM | A_ITALIC | COLOR_PAIR(1));

        // Credit text again
        printingCreditText(terHeight, terWidth, 0);

        // Replay the Game
        int quit = 0;

        while (chs = getch())
        {
            if (chs == 10 | chs == KEY_ENTER) // Waiting for ENTER press
            {
                break;
            }
            else if (chs == 113)
            {
                quit = 1;
                break;
            }
        }

        // Deleting all the windows
        delwin(welcomeWin);
        delwin(wrongCharWin);
        delwin(modeWin);
        delwin(timeOptWin);
        delwin(timeoutWin);
        delwin(generatedTextWin);
        delwin(challange);
        delwin(sec1);
        delwin(sec1_);
        delwin(sec2);
        delwin(sec2_);
        delwin(sec3);
        delwin(sec3_);
        delwin(sec4);
        delwin(sec4_);
        delwin(sec5);
        delwin(sec5_);
        delwin(sec6);
        delwin(sec6_);
        delwin(sec7);
        delwin(sec7_);
        delwin(sec8);
        delwin(sec8_);
        delwin(sec9);
        delwin(sec9_);
        delwin(sec10);
        delwin(sec10_);

        if (quit)
        {
            clear();
            refresh();

            // Thank you note for playing the game
            move(terHeight / 2, (terWidth - 11) / 2);
            attron(COLOR_PAIR(1) | A_STANDOUT | A_BOLD);
            printw(" THANK YOU ");
            attroff(COLOR_PAIR(1) | A_STANDOUT | A_BOLD);
            refresh();
            usleep(2000000);
            clear();

            break;
        }
        clear();
        refresh();
        getch();
    }

    // Ending the game
    refresh();
    endwin();
    return 0;
}