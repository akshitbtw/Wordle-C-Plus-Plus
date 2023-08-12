#include<bits/stdc++.h>
#include<graphics.h>

using namespace std;

#define X getmaxx()
#define Y getmaxy()

int main_window;

struct Player
{
    string Name;
    int Score;
};

istream& operator >>(std::istream& is, Player& s)
{
    return is >> s.Name >> s.Score;
}

class game
{
    // Board Top Left Corner Co-ordinates
    int rx, ry, x, y;// x,y - character location coordinates
    int i, j, l, m, count, flag_counter, row; // i,j - store, l,m - location
    int loc[50][3]; // x , y coordinate + input character
    int occurence[5];
    char name[50], input, word[6], store[10][5], temp[100], flag[6][5], time_elapsed[50];
    bool isCorrect;
    char player_name[30];
    int score, level;
    
public:

    game() : store{{0}}, flag{{0}}, loc{{0}}, player_name{0}
    {
        // Board Top Left Corner Co-ordinates
        rx=70, ry=110, x = 100, y=140;// x,y - character location coordinates
        i=0, j=0, l=0, m=0, count=0, flag_counter=0, row=0; // i,j - store, l,m - location
        occurence[5]={0};
        name[50]={0}, input, word[6]={0}, temp[100]={0}, time_elapsed[50]={0};
        score=0;   level = 0;
        isCorrect = false;
    }

    void reset(void)
    {
        isCorrect = false;
        memset(word, 0, sizeof word);
        rx=70, ry=110, x = 100, y=140;
        i=0, j=0, l=0, m=0,count=0, flag_counter=0, row=0;
        name[50]={0}, input, word[6]={0};
        fetch_word();   cleardevice();  board();
        memset(flag, 0, sizeof flag);
        memset(temp, 0, sizeof temp);
        memset(store, 0, sizeof store);
        memset(loc, 0, sizeof loc);
    }

    void board(void)
    {
        settextjustify(0,2);
        setcolor(9);
        setlinestyle(0,0,2);
        rectangle(rx-50,ry-90,X-20,Y-20);
        settextstyle(10,0,7); // 3 0 6 old
        setcolor(13);
        outtextxy(X/2+170,36,"WORDLE");
        setcolor(9);
        line(X/2+90,20,X/2+90,Y-20); // Middle Vertical Line
        line(X/2+90,110,X-20,110); // Wordle Below Border Horizontal Line
        line(X/2+90,120,X-20,120); // Wordle Below Border Horizontal Line
        line(X/2+115,20,X/2+115,110); // inside left vertical line
        line(X-45,20,X-45,110); // inside right vertical line
        setfillstyle(4,9);
        // floodfill(X/2+105,30,9);
        // floodfill(X-40,30,9);
        
        line(X/2+90,283,X-20,283); // after MESSAGE BOX horizontal line
        line(X/2+90,440,X-20,440); // after NAME SCORE Box 1st horizontal line
        line(X/2+90,445,X-20,445); // after NAME SCORE Box 2nd horizontal line
        // line(X/2+90,425,X-20,425); // after color boxes horizontal line

        // before message box horizontal lines
        // line(X/2+90,575,X-20,575);
        setcolor(15);
        setlinestyle(0,0,3);
        rectangle(rx-20,ry-20,570,720); // Outer Rectangle
        
        setcolor(12);
        settextstyle(10,0,4);
        outtextxy(X/2+180, 143, "MESSAGE BOX");
        rectangle(X/2+100,135,X-30,265);
        line(X/2+100,182,X-30,182);
        
        settextstyle(10,0,4);
        setcolor(12);
        outtextxy(X/2+101, 460, "COLOR REPRESENTATION");
        line(X/2+103,490,X-33,490); // underline // 175 175
        line(X/2+103,495,X-33,495); // underline // 180 180
        settextstyle(3,0,3);
        setcolor(10);
        setfillstyle(4, 10);
        rectangle(X/2+105, 525, X/2+145, 565);
        outtextxy(X/2+160, 532, "Correct Character & Correct Position");
        floodfill(X/2+135, 527, 10);

        setcolor(14);
        rectangle(X/2+105, 595, X/2+145, 635);
        setfillstyle(4, 14);
        outtextxy(X/2+155, 602, "Correct Character & Incorrect Position");
        floodfill(X/2+135, 600, 14);

        setcolor(7);
        rectangle(X/2+105, 665, X/2+145, 705);
        setfillstyle(4, 7);
        outtextxy(X/2+235, 672, "Wrong Character");
        floodfill(X/2+135, 670, 7);

        setcolor(12);
        settextstyle(10,0,4);
        rectangle(X/2+110,300,X-40,420); // 440 560
        outtextxy(X/2+123,315,"NAME");
        line(X/2+230,300,X/2+230,420); // after NAME vertical line
        setcolor(11);
        outtextxy(X/2+250,315,player_name);
        setcolor(12);
        line(X/2+110,360,X-40,360); // Below name horizontal line
        outtextxy(X/2+123,375,"SCORE");
        char score1[20];
        if(level == 1 || level == 2)
        {
            strcpy(score1,"NA");
            setcolor(11);
            outtextxy(X/2+250,375,score1);
            setcolor(12);
        }
        else
        {
            sprintf(score1,"%d", score);
            setcolor(11);
            outtextxy(X/2+250,375,score1);
            setcolor(12);
        }
        
        // Board
        setcolor(15);
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                rectangle(rx,ry,rx+80,ry+80);
                rx+=100;
            }
            rx=70;
            ry+=100;
        }
        rx=70, ry=110;
        if(level==1)
        {
            settextstyle(10,0,4);
            outtextxy(140, 40, "Time Remaining : NA  ");
        }
        settextstyle(4,0,3);
    }
    
    void fetch_word(void)
    {
        string line;
        int random = 0;
        int numOfLines = 0;
        ifstream File("words.txt");

        srand(time(0));
        random = rand() % 2313;

        while(getline(File, line))
        {
            ++numOfLines;

            if(numOfLines == random)
            {
                // cout << "String = "<<line;
                strcpy(word,line.c_str());
                break;
            }
        }
        cout<<word<<endl;
    }

    int check_entered_word(char word_check[])
    {
        string line;
        int random = 0;
        int numOfLines = 0;
        ifstream File("words.txt");

        while(getline(File, line))
        {
            ++numOfLines;
            if(strcmp(line.c_str(), word_check)==0)
            {
                // cout<<"WORD IN LIST "<<numOfLines<<endl;
                return 1;
                // break;
            }
            else if(File.eof())
                return 0;
        }
    }

    void count_characters(void)
    {
        char skip[5];
        // cout<<word<<endl;
        for(int i=0; i<5; i++)
        {
            char c = word[i];
            if(c==skip[0] || c==skip[1] || c==skip[2] || c==skip[3] || c==skip[4])
                continue;
            for(int j=0; j<5; j++)
            {
                if(c==word[j])
                {
                    occurence[i]+=1;
                    skip[i] = c;
                }     
            }
        }
        // cout<<"Occurence Before : "<<occurence[0]<<occurence[1]<<occurence[2]<<occurence[3]<<occurence[4]<<endl;
    }

    void algorithm(char a[])
    {
        count_characters();
        int skip[5]={-1};
        string s(word); // converting array of characters to string type
        for(int i=0; i<5; i++)
        {
            if(a[i]==word[i])
            {
                flag[row][i]='Y';
                occurence[s.find(a[i])]-=1;
                skip[i]=i;
            }
        }
        for(int i=0; i<5; i++)
        {
            if(i==skip[i])
            {
                flag_counter++;
                continue;
            }
            for(int j=0; j<5; j++)
            {
                if(j==skip[j])
                {
                    continue;
                }
                if(a[i]==word[j] && i!=j && occurence[s.find(a[i])]>0)
                {
                    flag[row][flag_counter]='N';
                    occurence[s.find(a[i])]-=1;
                    break;
                }
                else
                {
                    flag[row][flag_counter]='0';
                }
            }  
            flag_counter++;      
        }
        if(flag[row][0]=='Y' && flag[row][1]=='Y' && flag[row][2]=='Y' && flag[row][3]=='Y' && flag[row][4]=='Y')
            isCorrect = true;
        memset(occurence, 0, sizeof occurence);
        flag_counter=0;
        row++;
    }

    void fill(char flag[][5], int count)
    {
        int x=0;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(flag[i][j]=='Y' && x<count)
                {
                    // cout<<x;
                    // printf("if");
                    setfillstyle(1,10);
                    floodfill(loc[x][0],loc[x][1],15);
                    x++;
                }
                else if(flag[i][j]=='N' && x<count)
                {
                    // cout<<x;
                    // printf("else1");
                    setfillstyle(1,14);
                    floodfill(loc[x][0],loc[x][1],15);
                    x++;
                }
                else if(flag[i][j]=='0' && x<count)
                {
                    // cout<<x;
                    // printf("else2");
                    setfillstyle(1,7);
                    floodfill(loc[x][0],loc[x][1],15);
                    x++;
                }
            }
            
        }
        // cout<<"row no = "<<row;
    }

    void game1(void)
    {
        fetch_word();
        time_t begin, end, elapsed_time;
        int key_check=0;
        char label[25]={0};
        if(level!=1)
        {
            time(&begin);
        }
        while(isCorrect!=true && i!=6) // word guessed or no of guesses = 6
        {
            if(kbhit())
            {
                input = toupper(getch());
                if(isalpha(input) && j<5 && i<6)
                {
                    if(j==0 || key_check==1)
                    {
                        cleardevice();  board(); fill(flag, count);
                        key_check=0;
                    }
                    store[i][j]=input;
                    loc[l][m]=x; loc[l][m+1]=y; loc[l][m+2]=store[i][j];
                    l++; m=0;                    
                    x+=100;
                    j++;
                    count++;
                    settextstyle(10,0,4);
                    setcolor(11);
                    sprintf(label,"%c key Pressed", input);
                    outtextxy(X/2+160, 210, label);
                    setcolor(15);
                    settextstyle(4,0,3);
                }
                else if(isalpha(input) && j>=5){}
                else if(input==8 && j>0) // Backspace
                {
                    x-=100;
                    j--;
                    l--;
                    loc[l][m+2]='\0';
                    count--;
                    key_check = 1;
                    cleardevice();  board(); fill(flag, count);
                    settextstyle(10,0,4);
                    setcolor(11);
                    outtextxy(X/2+160, 190, "Backspace Key");
                    outtextxy(X/2+210, 220, "Pressed");
                    setcolor(15);
                    settextstyle(4,0,3);
                }
                else if(input==13 && j==5 && i<6) // Enter 
                {
                    int valid = check_entered_word(store[i]);
                    if(valid == 1)
                    {
                        settextstyle(10,0,4);
                        setcolor(11);
                        outtextxy(X/2+133, 210, "Enter key Pressed");
                        setcolor(15);
                        settextstyle(4,0,3);
                        algorithm(store[i]);
                    }
                    else
                    {
                        settextstyle(10,0,4);
                        setcolor(11);
                        outtextxy(X/2+133, 210, "NOT IN WORD LIST");
                        setcolor(15);
                        settextstyle(4,0,3);
                        continue;
                    }
                    fill(flag, count);
                    x=100, y+=100;
                    i++;    j=0;
                }
                else if(input==13 && j!=5) // Enter pressed without entering 5 characters
                {
                    settextstyle(10,0,4);
                    setcolor(11);
                    outtextxy(X/2+120, 210, "NOT ENOUGH LETTERS");
                    setcolor(15);
                    settextstyle(4,0,3);
                    key_check = 1;
                }
                else
                {
                    settextstyle(10,0,4);
                    setcolor(11);
                    outtextxy(X/2+110, 210, "INVALID KEY PRESSED");
                    setcolor(15);
                    settextstyle(4,0,3);
                    key_check = 1;
                }
                for(int p=0; p<count; p++)
                {
                    sprintf(temp, "%c", loc[p][2]); // converting int value to char
                    outtextxy(loc[p][0], loc[p][1], temp); 
                }
            }
            if(level==2)
            {
                time(&end);
                elapsed_time = 60 - (end - begin);
                sprintf(time_elapsed, "Time Remaining : %d seconds  ", elapsed_time);
                outtextxy(80, 45, time_elapsed);
                if(elapsed_time==0)
                    break;
            }
            else if(level==3 && isCorrect == false)
            {
                time(&end);
                elapsed_time = 120 - (end - begin);
                sprintf(time_elapsed, "Time Remaining : %d seconds  ", elapsed_time);
                outtextxy(80, 45, time_elapsed);
                if(elapsed_time==0)
                    break;
            }
            else if(level==3 && isCorrect == true)
            {
                delay(500);
                score++;
                reset();
            }
        }
        if(level==3 && score!=0)
        {
            // Storing details in file
            char details[100];
            sprintf(details,"%s\t%d", player_name, score);
            ofstream out;

            out.open("Records.txt", ios_base::app);
            out<<details<<endl;
            out.close();
        }
    }

    void entername(void)
    {
        int i=0;
        char name[30], upper[30]={0}, dots[]="...", flag=1;
        initwindow(415,100,"ALERT",530,350);
        setcolor(12);
        rectangle(5,5,410,95);
        setcolor(15);
        settextstyle(3,0,3);
        outtextxy(35,25,"Please enter your Name in the terminal");
        outtextxy(35,50,"window.");
        cout<<"***(No Numbers & Special Characters Allowed)***";
        // Player Name
        cout<<"\n\nEnter Player Name : "; 
        cin.get(name, 30);
        // cout<<name<<endl;
        // checking if there is any special character/number in the name1
        while(flag==1)
        {
            for (i=0; i<strlen(name); i++)
            {
                // checking each character of the name for special character
                if(isalpha(name[i])==0)
                {
                    printf("Special Characters or Numbers are not allowed, Please re-enter name : ");
                    flag=1;
                    break;
                }
                else
                    flag=0;
            }
            fflush(stdin);
            if(flag==1)
                cin.get(name, 30);
            else if(flag==0)
            {
                // cout<<"length "<<strlen(name)<<endl;
                for(int j=0; j<strlen(name); j++)
                {
                    upper[j] = toupper(name[j]);
                }
                // cout<<"player_name "<<player_name<<"name "<<name<<endl;
                strcpy(player_name, upper);
                // cout<<player_name<<" length = "<<strlen(player_name)<<endl;
                break;
            }     
        }
        fflush(stdin);

        // if entered valid name's length is greater than 10
        if(strlen(player_name)>10)
        {
            player_name[strlen(player_name) - (strlen(player_name) - 7)]  = '\0';
            strncat(player_name, dots, 3);
        }
        
        printf("\nYou can proceed to the Main Window...");
        closegraph(CURRENT_WINDOW);
        setcurrentwindow(main_window);
        cleardevice();
        board();
        game1();
    }

    void set_level(int level)
    {
        this->level = level;
    }

    int get_level(void)
    {
        return level;
    }

    char* get_player_name(void)
    {
        return player_name;
    }

    int get_score(void)
    {
        return score;
    }

    char* get_correct_word(void)
    {
        return word;
    }


    bool check_result(void)
    {
        if(isCorrect == true)
            return true;
        else
            return false;
    }
};

class screens : public game
{
    char display[30][100];
    int a, b, count;
public:
    screens() : display{{0}}
    {
        a=X/2, b=200, count=10;
    }

    void fetch_data(void)
    {
        string heading;
        ifstream input("Records.txt");
        vector <Player> p;
        getline(input, heading);
        Player s;
        while (input >> s)
            p.push_back(s);
        
        // sorting
        sort(p.begin(), 
            p.end(), 
            [](Player& s1, Player& s2) { return s1.Score > s2.Score; });
        
        int i=0; char temp[100]={0};
        
        setcolor(11);
        for( Player &e : p )
        {
            strcpy(temp, (e.Name).c_str());
            sprintf(display[i], "%s %d", temp, e.Score);
            i++;
        }

        for(i=0; i<=sizeof(display)/sizeof(display[0])-1; i++)
        {
            if((display[i][0] != '\0') && count>0) // if string is not empty and count > 0
            {
                outtextxy(a,b,display[i]);
                b+=50;
                count--;   
            }
            else
                continue;
        }
    }

    void highscores(void)
    {
        cleardevice();
        settextjustify(1,1);
        settextstyle(3,0,3);
        int i=0, j=0, color=9;
        int x = getmaxx(), y = getmaxy(), input;
        
        setcolor(15);
        
        setcolor(15); 
        settextstyle(10,0,6);
        settextjustify(1,1);
        rectangle(40,40,x-40,y-40);
        rectangle(20,20,x-20,y-20);
        setcolor(13);
        //HEADING
        outtextxy(x/2+5,120,"HIGHSCORES (High Difficulty)");
        setlinestyle(0,0,2);
        line(80,135,x-85,135);
        line(80,140,x-85,140);
        settextstyle(8,0,5);

        // Display Records
        fetch_data();

        setcolor(10);
        
        // Left click
        POINT cursorPosition;
        int mx, my;

        // Resetting data members so that if Highscores section is opened again then the program is able to show the data again
        a=X/2, b=200, count=10;
        memset(display, 0, sizeof display);

        // back to main menu
        setcolor(14);
        settextstyle(10,0,4);
        outtextxy(x/2,y-60,"SPACEBAR / Left Mouse Click - Main Menu");
        rectangle(x/2-380,y-90,x/2-207,y-47); 
        setcolor(10);
        while(1) // Border Animation
        {
            if(color>14)
                color = 9;
            setfillstyle(4,color);
            floodfill(25,25,15);
            color++;
            delay(500);
            if(kbhit())
            {
                input = getch();
                if(input==32) // SPACEBAR
                {
                    cleardevice();
                    setbkcolor(0);
                    setcolor(15);
                    main_menu();
                    break;
                }
            }

            // Left Mouse Click
            GetCursorPos(&cursorPosition);

            mx = cursorPosition.x-233;
            my = cursorPosition.y-56;
            
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                cleardevice();
                setbkcolor(0);
                setcolor(15);
                main_menu();
                break;
            }
        }
    }

    void game_over_screen(void)
    {
        cleardevice();
        int x = getmaxx(), y = getmaxy(), color=10;
        char player_won[50]={0}, input, correct_word[10]={0}, word[30]={0};
        rectangle(30,30,x-30,y-30);
        color = 4;
        setfillstyle(SOLID_FILL,color);
        floodfill(55,55,15);
        setbkcolor(4);
        setcolor(15);
        settextjustify(1,1); // to centre align the text
        strcpy(correct_word, get_correct_word());
        sprintf(word, "The word was %s", correct_word);
        setcolor(15);
        settextstyle(10,0,9);
        outtextxy(x/2, y/2-80, "GAME OVER");
        settextstyle(10,0,6);
        outtextxy(x/2, y/2, word);
        setcolor(14);
        settextstyle(10,0,5);
        outtextxy(x/2,y-80,"SPACEBAR - Main Menu | ESC - Exit"); 
        color++;
        delay(500);
        while (1)
        {
            if(kbhit())
            {
                input = getch();
                if(input==32) // space
                {
                    reset();
                    setbkcolor(0);
                    cleardevice();
                    main_menu();
                    break;
                }
                if(input==27) // escape
                {
                    exit(0);
                }
            }
        }
    }

    void win_screen2(void) // high difficulty
    {
        setlinestyle(0,0,2);
        int x = getmaxx(), y = getmaxy(), color=10;
        char text[50], input, correct_word[10]={0}, word[30]={0};
        sprintf(text, "%d word(s) guessed correctly!", get_score());
        strcpy(correct_word, get_correct_word());
        sprintf(word, "The word was %s", correct_word);
        
        while(1)
        {
            cleardevice();
            rectangle(30,30,x-30,y-30);
            if(color>14)
                color = 10;
            setfillstyle(SOLID_FILL,color);
            floodfill(55,55,15);
            settextstyle(10,0,6);
            setbkcolor(color);
            setcolor(9);
            settextjustify(1,1); // to centre align the text
            outtextxy(x/2, y/2-50, text);
            outtextxy(x/2, y/2, word);
            setcolor(15);
            settextstyle(10,0,5);
            outtextxy(x/2,y-80,"SPACEBAR - Main Menu | ESC - Exit"); 
            color++;
            delay(500);
            if(kbhit())
            {
                input = getch();
                if(input==32) // space
                {
                    reset();
                    setbkcolor(0);
                    cleardevice();
                    main_menu();
                    break;
                }
                if(input==27) // escape
                {
                    exit(0);
                    break;
                }
            }
        }
    }

    void win_screen1(void)
    {
        setlinestyle(0,0,2);
        int x = getmaxx(), y = getmaxy(), color=10;
        char player_won[50], input;
        sprintf(player_won, "%s WON!", get_player_name());
        
        while(1)
        {
            cleardevice();
            rectangle(30,30,x-30,y-30);
            if(color>14)
                color = 10;
            setfillstyle(SOLID_FILL,color);
            floodfill(55,55,15);
            settextstyle(10,0,9);
            setbkcolor(color);
            setcolor(9);
            settextjustify(1,1); // to centre align the text
            outtextxy(x/2, y/2, player_won);
            setcolor(15);
            settextstyle(10,0,5);
            outtextxy(x/2,y-80,"SPACEBAR - Main Menu | ESC - Exit"); 
            color++;
            delay(500);
            if(kbhit())
            {
                input = getch();
                if(input==32) // space
                {
                    reset();
                    setbkcolor(0);
                    cleardevice();
                    main_menu();
                    break;
                }
                if(input==27) // escape
                {
                    exit(0);
                    break;
                }
            }
        }
    }

    void result(void)
    {
        char result = check_result();
        if(result == true)
        {
            win_screen1();            
        }
        else if(result == false && get_level()==3)
        {
            win_screen2();
        }
        else
        {
            game_over_screen();
        }
    }

    void difficulty(void)
    {
        setlinestyle(0,0,2);
        rectangle(20,20,X-20,Y-20);
        int n, x=90, y=85;
        char title[]={'M','A','I','N',' ','M','E','N','U'}, label[10];
        int colorfill[] = {10,14,7,14,0,10,7,10,14};
        settextjustify(1,1);
        settextstyle(10,0,6);
        for(int i=0; i<9; i++)
        {
            sprintf(label, "%c", title[i]);
            if(i==4)
            {
                x+=50;
                continue;
            }
            rectangle(x,y,x+90,y+90);
            rectangle(x+15,y+15,x+75,y+75);
            outtextxy(x+46, y+60, label);
            setfillstyle(1,colorfill[i]);
            floodfill(x+1,y+1,15);
            x+=100;
        }
        
        settextstyle(3,0,3);
        int a=90, b=242;
        char options[9][70]={
            "EASY",
            "NO Time Limit",
            "Number of words to be GUESSED = 1",

            "MEDIUM",
            "Time Limit (1 minute)",
            "Number of words to be GUESSED = 1",
            
            "HARD",
            "Time Limit (2 minutes)",
            "Number of words to be GUESSED = Unlimited",
        };

        // OPTIONS
        for(int i=0; i<9; i++)
        {
            if(i==0)
            {
                rectangle(a,b,a+423,b+100);
                outtextxy(X/2-210, b+30, options[i]);
                b+=25;
            }
            else if(i%3==0 && i!=0)
            {
                b+=45;
                rectangle(a,b,a+423,b+100);
                outtextxy(X/2-210, b+30, options[i]);
                b+=25;
            }
            else
            {
                outtextxy(X/2-210, b+30, options[i]);
                b+=25;
            }
        }
        setcolor(15);
        // BACK
        rectangle(200, 620, 400, 690);
        outtextxy(300,660,"BACK");
        // WORDLE BOARD TEMPLATE
        int rx = X/2+60, ry = 260;
        srand ( time(NULL) );
        int colors[3] = {10,14,7};

        setlinestyle(0,0,2);
        rectangle(X/2+40,240,X/2+420,690);
        setlinestyle(0,0,1);
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                rectangle(rx,ry,rx+60,ry+60);
                int RanIndex = rand() % 3;
                setfillstyle(1,colors[RanIndex]);
                floodfill(rx+2,ry+2,15);
                rx+=70;
            }
            rx=X/2+60;
            ry+=70;
        }

        delay(1000);
        POINT cursorPosition;
        int mx, my;
        while(1)
        {
            GetCursorPos(&cursorPosition);

            mx = cursorPosition.x-233;
            my = cursorPosition.y-56;
            
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mx>100 && mx<500 && my>242 && my<342) // EASY
                {
                    set_level(1);
                    entername();
                    result();
                    // reset();
                    break;
                }     
                else if(mx>100 && mx<500 && my>362 && my<462) // MEDIUM
                {
                    set_level(2);
                    entername();
                    result();
                    // reset();
                    break;
                }
                else if(mx>100 && mx<500 && my>482 && my<582) // HARD
                {
                    set_level(3);
                    entername();
                    result();
                    break;
                }
                else if(mx>200 && mx<400 && my>620 && my<690) // BACK
                {
                    cleardevice();
                    main_menu();
                    break;
                }
            }   
            delay(1);
        }
    }

    void main_menu(void)
    {
        setlinestyle(0,0,2);
        setcolor(15);
        rectangle(20,20,X-20,Y-20);
        int n, x=90, y=85;
        char title[]={'M','A','I','N',' ','M','E','N','U'}, label[10];
        int colorfill[] = {10,14,7,14,0,10,7,10,14};
        settextjustify(1,1);
        settextstyle(10,0,6);
        for(int i=0; i<9; i++)
        {
            sprintf(label, "%c", title[i]);
            if(i==4)
            {
                x+=50;
                continue;
            }
            rectangle(x,y,x+90,y+90);
            rectangle(x+15,y+15,x+75,y+75);
            outtextxy(x+46, y+60, label);
            setfillstyle(1,colorfill[i]);
            floodfill(x+1,y+1,15);
            x+=100;
        }
        
        settextstyle(10,0,4);
        int a=100, b=250, color=9;
        char options[5][15]={"New Game","How to Play","Highscores","About the Game","EXIT"};
        // OPTIONS
        for(int i=0; i<5; i++)
        {
            setcolor(color);
            rectangle(a,b,a+400,b+70);
            outtextxy(X/2-210,b+45,options[i]);
            b+=90;
            color++;
        }

        // WORDLE BOARD TEMPLATE
        int rx = X/2+60, ry = 260;
        srand(time(NULL));
        int colors[3] = {10,14,7};
        setcolor(15);
        setlinestyle(0,0,2);
        rectangle(X/2+40,240,X/2+420,690);
        setlinestyle(0,0,1);
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<5; j++)
            {
                rectangle(rx,ry,rx+60,ry+60);
                int RanIndex = rand() % 3;
                setfillstyle(1,colors[RanIndex]);
                floodfill(rx+2,ry+2,15);
                rx+=70;
            }
            rx=X/2+60;
            ry+=70;
        }

        delay(1000);
        POINT cursorPosition;
        int mx, my;
        while(1)
        {
            GetCursorPos(&cursorPosition);

            mx = cursorPosition.x-233;
            my = cursorPosition.y-56;
            
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(mx>100 && mx<500 && my>250 && my<320) // NEW GAME
                {
                    cleardevice();
                    difficulty();
                    break;
                }     
                else if(mx>100 && mx<500 && my>340 && my<410) // Option 2
                {
                    howtoplay();    break;
                }
                else if(mx>100 && mx<500 && my>430 && my<500) // Option 3
                {
                    highscores();   break;
                }
                else if(mx>100 && mx<500 && my>520 && my<590) // Option 4
                {
                    about();    break;
                }
                else if(mx>100 && mx<500 && my>610 && my<680) // Option 5
                {
                    exit(0);
                }
            }   
            delay(1);
        }
    }


    void about(void)
    {
        cleardevice();
        int i,j,color=9, x=X, y = Y;
        int input=0;
        setcolor(15);
        rectangle(30,30,x-30,y-30);
        rectangle(15,15,x-15,y-15);
        setcolor(13);
        //HEADING
        settextstyle(3,0,6);
        settextjustify(1,1);
        outtextxy(x/2,100,"About the Game");
        setlinestyle(0,0,2);
        line(x/2-200,115,x/2+200,115);
        line(x/2-200,120,x/2+200,120);

        //RULES
        setcolor(11);
        settextjustify(1,1);
        settextstyle(10,0,4);
        outtextxy(x/2,190,"- Wordle is a web-based word game created and");
        outtextxy(x/2,230,"developed by Welsh software engineer Josh Wardle,");
        outtextxy(x/2,270,"and owned and published by The New York Times");
        outtextxy(x/2,310,"Company since 2022.");
        outtextxy(x/2,360,"- It's fun, simple and, like a crossword, can");
        outtextxy(x/2,400,"only be played once a day.");
        outtextxy(x/2,450,"- Every 24 hours there's a new word of the day,");
        outtextxy(x/2,490,"and it's up to you to figure out what it is.");
        outtextxy(x/2,530,"word.");
        outtextxy(x/2,580,"- Wordle gives players six chances to guess a ");
        outtextxy(x/2,620,"randomly selected five-letter word.");
        // Left click
        POINT cursorPosition;
        int mx, my;

        // back to main menu
        setcolor(14);
        settextstyle(10,0,3);
        outtextxy(x/2,y-60,"SPACEBAR - Main Menu | Left Mouse Click - How to Play");
        rectangle(x/2-380,y-85,x/2-250,y-47); 
        setcolor(10);
        while(1) // Border Animation
        {
            if(color>14)
                color = 9;
            setfillstyle(4,color);
            floodfill(25,25,15);
            color++;
            delay(500);
            if(kbhit())
            {
                input = getch();
                if(input==32) // SPACEBAR
                {
                    cleardevice();
                    setbkcolor(0);
                    setcolor(15);
                    main_menu();
                    break;
                }
            }

            // Left Mouse Click
            GetCursorPos(&cursorPosition);

            mx = cursorPosition.x-233;
            my = cursorPosition.y-56;
            
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                cleardevice();
                setbkcolor(0);
                setcolor(15);
                howtoplay();
                break;
            }
        }
    }

    void howtoplay(void)
    {
        cleardevice();
        int i,j,color=9, x=X, y = Y;
        int input=0;
        setcolor(15);
        rectangle(30,30,x-30,y-30);
        rectangle(15,15,x-15,y-15);
        setcolor(13);
        //HEADING
        settextstyle(3,0,6);
        settextjustify(1,1);
        outtextxy(x/2,100,"How to Play");
        setlinestyle(0,0,2);
        line(x/2-150,115,x/2+150,115);
        line(x/2-150,120,x/2+150,120);

        //RULES
        setcolor(11);
        settextjustify(1,1);
        settextstyle(10,0,4);
        outtextxy(x/2,180,"- Guess the WORDLE in 6 tries.");
        outtextxy(x/2,230,"- Each guess must be a five-letter word. Hit ");
        outtextxy(x/2,260,"ENTER button to submit.");
        outtextxy(x/2,310,"- After each guess, the color of the tiles will");
        outtextxy(x/2,340,"change to show how close your guess was to the");
        outtextxy(x/2,370,"word.");

        // EXAMPLES
        outtextxy(x/2-340,460,"EXAMPLES: ");
        line(x/2-435,470,x/2-285,470);
        line(x/2-435,475,x/2-285,475);
        
        setcolor(15);
        int n, a=x/2-245, b=420;
        char title[]={'W','E','A','R','Y'}, label[10];
        settextstyle(10,0,3);
        for(int i=0; i<5; i++)
        {
            sprintf(label, "%c", title[i]);
            rectangle(a,b,a+60,b+60);
            rectangle(a+12,b+12,a+48,b+48);
            outtextxy(a+30, b+35, label);
            a+=70;
        }
        // W - GREEN
        setfillstyle(1,10);
        floodfill(x/2-240+1,421,15);

        a=x/2-245, b=500;
        char title1[]={'P','I','L','L','S'};
        settextstyle(10,0,3);
        for(int i=0; i<5; i++)
        {
            sprintf(label, "%c", title1[i]);
            rectangle(a,b,a+60,b+60);
            rectangle(a+12,b+12,a+48,b+48);
            outtextxy(a+30, b+35, label);
            a+=70;
        }
        // I - YELLOW
        setfillstyle(1,14);
        floodfill(x/2-240+70+1,501,15);

        a=x/2-245, b=580;
        char title2[]={'V','A','G','U','E'};
        settextstyle(10,0,3);
        for(int i=0; i<5; i++)
        {
            sprintf(label, "%c", title2[i]);
            rectangle(a,b,a+60,b+60);
            rectangle(a+12,b+12,a+48,b+48);
            outtextxy(a+30, b+35, label);
            a+=70;
        }
        // U - GREY
        setfillstyle(1,7);
        floodfill(x/2-240+70+70+70+1,581,15);

        // Explanation
        setcolor(10);
        outtextxy(x-230,440,"The letter W is in the");
        outtextxy(x-230,460,"word and in the correct");
        outtextxy(x-230,480,"spot.");

        outtextxy(x-230,520,"The letter I is in the");
        outtextxy(x-230,540,"word but in the wrong");
        outtextxy(x-230,560,"spot.");
        
        outtextxy(x-230,610,"The letter U is not in");
        outtextxy(x-230,630,"the word at any spot");

        // Left click
        POINT cursorPosition;
        int mx, my;

        //NEXT SCREEN
        setcolor(14);
        settextstyle(10,0,4);
        outtextxy(x/2,y-60,"Press SPACEBAR / Left Mouse Click to Continue");
        rectangle(x/2-320,y-90,x/2-155,y-47); 
        setcolor(10);
        while(1) // Border Animation
        {
            if(color>14)
                color = 9;
            setfillstyle(4,color);
            floodfill(25,25,15);
            color++;
            delay(500);
            if(kbhit())
            {
                input = getch();
                if(input==32) // SPACEBAR
                {
                    cleardevice();
                    setbkcolor(0);
                    setcolor(15);
                    main_menu();
                    break;
                }
            }

            // Left Mouse Click
            GetCursorPos(&cursorPosition);

            mx = cursorPosition.x-233;
            my = cursorPosition.y-56;
            
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                cleardevice();
                setbkcolor(0);
                setcolor(15);
                main_menu();
                break;
            }
        }
    }

    void loading(void)
    {
        int n, x=155, y=100;
        char title[]={'W','O','R','D','L','E'}, label[10];
        int bar = X/2-296;
        settextjustify(1,1);
        settextstyle(10,0,7);
        for(int i=0; i<6; i++)
        {
            sprintf(label, "%c", title[i]);
            rectangle(x,y,x+100,y+100);
            rectangle(x+15,y+15,x+85,y+85);
            outtextxy(x+53, y+67, label);
            x+=120;
        }
        // Coloring TITLE
        setfillstyle(SOLID_FILL, 15);
        floodfill(411,101,15); // 3rd char
        floodfill(651,101,15); // 5th char
        setfillstyle(SOLID_FILL, 10);
        floodfill(171,101,15); // 1st char
        floodfill(531,101,15); // 4th char
        setfillstyle(SOLID_FILL,14);
        floodfill(291,101,15); // 2nd char
        floodfill(771,101,15); // 6th char
        settextstyle(8,0,5);
        // sprintf(label, "%c Akshit", (wchar_t)0xA9);
        outtextxy(X/2+230, 250, "By Akshit");

        // LOADING ANIMATION
        settextstyle(3,0,6);
        setcolor(15);
        rectangle(10,10,X-10,Y-10); // Loading Screen Border
        setlinestyle(0,0,2);
        outtextxy(X/2,Y/2+70,"Loading...");
        rectangle(X/2-300,Y/2+100,X/2+300,Y/2+151); // Loading Bar Border
        delay(1000);
        while(bar!=X/2+296)
        {   
            rectangle(X/2-296,Y/2+105,bar,Y/2+146);
            if(bar==X/2-180 || bar==X/2+70 || bar==X/2+270)
                delay(1000);
            bar++;
        }
        delay(500);
        about();
    }
};

int main()
{
    main_window = initwindow(1024,768,"WORDLE",230,30);
    screens sc;

    sc.loading();
    // sc.main_menu();
    
    getch();
    return 0;
}