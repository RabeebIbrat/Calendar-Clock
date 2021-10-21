#include "iGraphics.h"

//Calendar Variables
const int mon_x = 80, mon_y = 305, mon_ryt = 160, mon_up = 42;
char mon[10] = {}, mon2[10] = {};
int mon_len = 0, mode = 0;
const int write_up = 15, write_ryt = 10;
int year = 2017, month = 4, days = 30, leap = 0;
char monvu[10] = "April";
const int cal_x = 83, cal_y = 200, cal_ryt = 40, cal_down = 30;
int cal_init = 6, point_x, point_y, cal_res;
char day[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

const int yr_x = 270, yr_y = 305, yr_ryt = 68, yr_up = 42;
char yr[5] = {}, yr2[5] = "2017";
int yr_len = 0;

//Clock Variables
int hour, mint, sec;
const int dig_x = 400, dig_y = 130, dig_ryt = 20, dig_thick = 7, dig_long = 50, point_ycal = 15, point_rad = 5;

//*********Calendar*********
int zeller(int month, int year)
{
    int day_1;
    month -= 2;
    if(month <= 0)
        month += 12;
    if(month >= 11)
        year--;
    int dig = year % 100;
    int cent = year / 100;
    day_1 = 1 + (13 * month - 1) / 5 + dig + dig / 4 + cent / 4 - 2 * cent;
    day_1 %= 7;
    if(day_1 < 0)
        day_1 += 7;
    return day_1;
}

int year_get(char yr2[0])
{
    int yaiks[4];
    for(int i = 0; i < 4; i++){
        yaiks[i] = yr2[i] - '0';
    }
    year = yaiks[3] + 10 * yaiks[2] + 100 * yaiks[1] + 1000 * yaiks[0];
    return year;
}

void headText()
{
    iSetColor(197, 198, 201);
    iText(mon_x + write_ryt, mon_y + mon_up + 20, "Month: ", GLUT_BITMAP_HELVETICA_18);
    iText(yr_x + write_ryt, yr_y + yr_up + 20, "Year: ", GLUT_BITMAP_HELVETICA_18);
}

void monBox()
{
    iSetColor(197, 198, 201);
    iRectangle(mon_x, mon_y, mon_ryt, mon_up);

}

void yrBox()
{
    iSetColor(197, 198, 201);
    iRectangle(yr_x, yr_y, yr_ryt, yr_up);

}

void monText()
{
    iSetColor(76, 139, 239);
    iText(mon_x + write_ryt, mon_y + write_up, mon, GLUT_BITMAP_TIMES_ROMAN_24);

}

void yrText()
{
    iSetColor(76, 139, 239);
    iText(yr_x + write_ryt, yr_y + write_up, yr, GLUT_BITMAP_TIMES_ROMAN_24);

}

void calTit()
{
    for(int i = 0; i < 7; i++)
        iText(cal_x  + i * cal_ryt, cal_y, day[i]);
}

void calBod()
{
    point_x = cal_x + cal_init * cal_ryt;
    point_y = cal_y - cal_down;
    cal_res = cal_init;
    char date[4] = "001";
    char print[4];
    int i, j;
    for(i = 1; i <= days + leap; i++)
    {
        strcpy(print, date);
        for(j = 0; j < 3 && print[j] == '0'; j++){
            print[j] = ' ';
        }
        iText(point_x, point_y, print);
        point_x += cal_ryt;
        cal_res++;
        if(cal_res == 7){
            cal_res = 0;
            point_y -= cal_down;
            point_x = cal_x;
        }
        if(date[2] < '9')
            date[2]++;
        else{
            date[1]++;
            date[2] = '0';
        }
    }
}

void cal()
{
    iSetColor(48, 193, 133);
    calTit();
    calBod();
}
//**********Clock**********
void digPrint(int x, int y, int val)
{
    /*digitalWrite
    |--1--|
    |4   5|
    |--2--|
    |6   7|
    |--3--|
    */
    if(val == 0 || val == 2 || val == 3 || val == 5 || val == 6 || val == 7 || val == 8 || val == 9)
        iFilledRectangle(x, y + 2 * (dig_thick + dig_long), 2 * dig_thick + dig_long, dig_thick);   //Unit 1
    if(val == 2 || val == 3 || val == 4 || val == 5 || val == 6 || val == 8 || val == 9)
        iFilledRectangle(x, y + 1 * (dig_thick + dig_long), 2 * dig_thick + dig_long, dig_thick);   //Unit 2
    if(val == 0 || val == 2 || val == 3 || val == 5|| val == 6 || val == 8 || val == 9)
        iFilledRectangle(x, y + 0 * (dig_thick + dig_long), 2 * dig_thick + dig_long, dig_thick);   //Unit 3
    if(val == 0 || val == 4 || val == 5 || val == 6 || val == 8 || val == 9)
        iFilledRectangle(x, y + (dig_thick  + dig_long), dig_thick, 2 * dig_thick + dig_long);  //Unit 4
    if(val == 0 || val == 1 || val == 2 || val == 3 || val == 4 || val == 7 || val == 8 || val == 9)
        iFilledRectangle(x + (dig_thick + dig_long), y + (dig_thick  + dig_long), dig_thick, 2 * dig_thick + dig_long); //Unit 5
    if(val == 0 || val == 2 || val == 6 || val == 8)
        iFilledRectangle(x, y, dig_thick, 2 * dig_thick + dig_long);  //Unit 6
    if(val == 0 || val == 1 || val == 3 || val == 4 || val == 5 || val == 6 || val == 7 || val == 8 || val == 9)
        iFilledRectangle(x + (dig_thick + dig_long), y, dig_thick, 2 * dig_thick + dig_long); //Unit 7

}

void clock(int hour, int mint, int sec)
{
    int h1 = hour / 10, h2 = hour % 10;
    int m1 = mint / 10, m2 = mint % 10;
    int s1 = sec / 10, s2 = sec % 10;

    int pos_x = dig_x, pos_y = dig_y, point_y = dig_y + (3 * dig_thick) / 2 + dig_long;
    digPrint(pos_x, pos_y, h1);
    pos_x += (2 * dig_thick + dig_long+ dig_ryt);
    digPrint(pos_x, pos_y, h2);
    pos_x += (2 * dig_thick + dig_long+ dig_ryt);
    iPoint(pos_x, point_y + point_ycal, point_rad);
    iPoint(pos_x, point_y - point_ycal, point_rad);
    pos_x += dig_ryt;
    digPrint(pos_x, pos_y, m1);
    pos_x += (2 * dig_thick + dig_long+ dig_ryt);
    digPrint(pos_x, pos_y, m2);
    pos_x += (2 * dig_thick + dig_long+ dig_ryt);
    iPoint(pos_x, point_y + point_ycal, point_rad);
    iPoint(pos_x, point_y - point_ycal, point_rad);
    pos_x += dig_ryt;
    digPrint(pos_x, pos_y, s1);
    pos_x += (2 * dig_thick + dig_long+ dig_ryt);
    digPrint(pos_x, pos_y, s2);
}

void iDraw()
{

    iClear();
    headText();
    monBox();
    monText();
    yrBox();
    yrText();
    //Calendar Heading
    iSetColor(48, 193, 133);
    iText(155, 240, monvu, GLUT_BITMAP_9_BY_15);
    iText(240, 240, yr2, GLUT_BITMAP_9_BY_15);
    cal();
    {
        time_t t = time(NULL);
        hour = localtime(&t)->tm_hour;
        mint = localtime(&t)->tm_min;
        sec = localtime(&t)->tm_sec;
    }
    iSetColor(186, 78, 78);
    clock(hour, mint, sec);
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mode == 0){
        if(mx >= mon_x && my > mon_y && mx < (mon_x + mon_ryt) && my <= (mon_y + mon_up)){
            mode = 1;
            printf("Enter month: ");
        }
        else if(mx > yr_x && my >yr_y && mx < (yr_x + yr_ryt) && my <= (yr_y + yr_up)){
            mode = 2;
            printf("Enter year: ");
        }
    }
}

void iKeyboard(unsigned char key)
{
    int i;
    if(mode == 1)
    {
        if(key == '\r'){
            mode = 0;
            strcpy(mon2, mon);
            printf("%s\n", mon2);
            for(i = 0; i < mon_len; i++)
                mon[i] = 0;
            mon_len = 0;
            {
                if(mon2[0] == 'J' && mon2[1] == 'A' && mon2[2] == 'N'){
                    month = 1; days = 31; strcpy(monvu, "January");}
                else if(mon2[0] == 'F' && mon2[1] == 'E' && mon2[2] == 'B'){
                    month = 2; days = 28; strcpy(monvu, "February");}
                else if(mon2[0] == 'M' && mon2[1] == 'A' && mon2[2] == 'R'){
                    month = 3; days = 31; strcpy(monvu, "March");}
                else if(mon2[0] == 'A' && mon2[1] == 'P' && mon2[2] == 'R'){
                    month = 4; days = 30; strcpy(monvu, "April");}
                else if(mon2[0] == 'M' && mon2[1] == 'A' && mon2[2] == 'Y'){
                    month = 5; days = 31; strcpy(monvu, "May");}
                else if(mon2[0] == 'J' && mon2[1] == 'U' && mon2[2] == 'N'){
                    month = 6; days = 30; strcpy(monvu, "June");}
                else if(mon2[0] == 'J' && mon2[1] == 'U' && mon2[2] == 'L'){
                    month = 7; days = 31; strcpy(monvu, "July");}
                else if(mon2[0] == 'A' && mon2[1] == 'U' && mon2[2] == 'G'){
                    month = 8; days = 31; strcpy(monvu, "August");}
                else if(mon2[0] == 'S' && mon2[1] == 'E' && mon2[2] == 'P'){
                    month = 9; days = 30; strcpy(monvu, "September");}
                else if(mon2[0] == 'O' && mon2[1] == 'C' && mon2[2] == 'T'){
                    month = 10; days = 31; strcpy(monvu, "October");}
                else if(mon2[0] == 'N' && mon2[1] == 'O' && mon2[2] == 'V'){
                    month = 11; days = 30; strcpy(monvu, "November");}
                else if(mon2[0] == 'D' && mon2[1] == 'E' && mon2[2] == 'C'){
                    month = 12; days = 31; strcpy(monvu, "December");}
            }

            leap = 0;
            if(month == 2){
                if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
                    leap = 1;
                }
            }
            cal_init = zeller(month, year);
        }
        else if(key == '\b' && mon_len > 0){
            mon_len--;
            mon[mon_len] = 0;
        }
        else if('A' <= key && key <= 'Z' && mon_len < 9){
            mon[mon_len] = key;
            mon_len++;
        }
        else if('a' <= key && key <= 'z' && mon_len < 9){
            key = key - 'a' + 'A';
            mon[mon_len] = key;
            mon_len++;
        }
    }

    if(mode == 2)
    {
        if(key == '\r'){
            mode = 0;
            int loop = 1;
            while(yr[3] == 0 && loop <= 4){
                for(i = 3; i > 0; i--)
                    yr[i] = yr[i - 1];
                yr[0] = '0';
                loop++;
            }
            strcpy(yr2, yr);
            printf("%s\n", yr2);
            for(i = 0; i < 4; i++)
                yr[i] = 0;
            yr_len = 0;
            year = year_get(yr2);
            leap = 0;
            if(month == 2){
                if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
                    leap = 1;
                }
            }
            cal_init = zeller(month, year);
        }
        else if(key == '\b' && yr_len > 0){
            yr_len--;
            yr[yr_len] = 0;
        }
        else if('0' <= key && key <= '9' && yr_len < 4){
            yr[yr_len] = key;
            yr_len++;
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END)
        exit(0);
}

int main()
{
    iInitialize(1000, 430, "Calender Clock");
    return 0;
}
