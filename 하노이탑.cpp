#include <stdio.h>
#include<bangtal.h>
#include <stdlib.h>
#include <time.h>

SceneID start_scene, hanoi_tower;
ObjectID start_button, end_button, p1, p2, p3, p4, p5, p6;
TimerID timerMixing;
const Second animationTime = 0.5f;

int Y[7] = {0,74,151,224,295,367,442};
int X[7][4] = {
    0,0,0,0,
    0,15,441,871,
    0,54,482,912,
    0,87,519,949,
    0,120,552,982,
    0,154,578,1008,
    0,189,613,1043 };
int a[63];
int b[63];

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown == true) {
        showObject(object);
    }
    return object;
}


void scene_create() {

    start_scene = createScene("start", "hanoi.png");
    hanoi_tower = createScene("Hanoi Tower", "hanoi.png");
}

void object_create() {
    //start
    start_button = createObject("start.png", start_scene, 590, 270, true);
    end_button = createObject("end.png", start_scene, 590, 220, true);

    //hanoi  
    //여기서의 '층'과 p(n)은 조각 크기가 작은순서와 동일함. ex) 가장 높이 있는것이 1층(p1)
    //배열의 경우는 실제 층수와 동일함. 
    p1 = createObject("1층.png", hanoi_tower, X[6][1], Y[6], true);
    p2 = createObject("2층.png", hanoi_tower, X[5][1], Y[5], true);
    p3 = createObject("3층.png", hanoi_tower, X[4][1], Y[4], true);
    p4 = createObject("4층.png", hanoi_tower, X[3][1], Y[3], true);
    p5 = createObject("5층.png", hanoi_tower, X[2][1], Y[2], true);
    p6 = createObject("6층.png", hanoi_tower, X[1][1], Y[1], true);
    end_button = createObject("end.png", hanoi_tower, 590, 220, false);

}
int pi1 = 1, pi2 = 1, pi3 = 1, pi4 = 1, pi5 = 1, pi6 = 1;

int count;

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == end_button) {
        endGame();
    }
    else if (object == start_button) {
        enterScene(hanoi_tower);
        timerMixing = createTimer();
        setTimer(timerMixing, animationTime);
        startTimer(timerMixing);
    }
}

//프린트 함수
/*void move(int from, int to)
{
    printf("%d %d\n", from, to);

}*/

int h = 1;
void hanoi(int n, int from, int extra, int to)
{
   
    if (n == 1) {
       //move(from, to);
        a[h] = from;
        b[h] = to;
        h++;
    }

    else {
        hanoi(n - 1, from, to, extra);
        //move(from, to);
        a[h] = from;
        b[h] = to;
        h++;
        hanoi(n - 1, extra, from, to);
    }
}
int g = 1;
void timerCallback(TimerID timer) {
    int m = a[g];
    int n = b[g];
    int floor = 1;
    if (pi1 == 2 && pi2 == 2 && pi3 == 2 && pi4 == 2 && pi5 == 2 && pi6 == 2) {
        stopTimer(timerMixing);
        showObject(end_button);
    }
    else if (pi1 == m) {
        if (pi6 == n) {
            floor++;
        }
        if (pi5 == n) {
            floor++;
        }
        if (pi4 == n) {
            floor++;
        }  
        if (pi3 == n) {
            floor++;
        }
        if (pi2 == n) {
            floor++;
        }
        locateObject(p1, hanoi_tower, X[6][n], Y[floor]);
        pi1 = n;
    }
    else if (pi1 != m && pi2 == m) {
        if (pi6 == n) {
            floor++;
        }
        if (pi5 == n) {
            floor++;
        }
        if (pi4 == n) {
            floor++;
        }
        if (pi3 == n) {
            floor++;
        }
        locateObject(p2, hanoi_tower, X[5][n], Y[floor]);
        pi2 = n;
    }
    else if (pi1 != m && pi2 != m && pi3 == m) {
        if (pi6 == n) {
            floor++;
        }
        if (pi5 == n) {
            floor++;
        }
        if (pi4 == n) {
            floor++;
        }
        locateObject(p3, hanoi_tower, X[4][n], Y[floor]);
        pi3 = n;
    }
    else if (pi1 != m && pi2 != m && pi3 != m && pi4 == m) {
        if (pi6 == n) {
            floor++;
        }
        if (pi5 == n) {
            floor++;
        }
        locateObject(p4, hanoi_tower, X[3][n], Y[floor]);
        pi4 = n;
    }
    else if (pi1 != m && pi2 != m && pi3 != m && pi4 != m && pi5 == m) {
        if (pi6 == n) {
            floor++;
        }
        locateObject(p5, hanoi_tower, X[2][n], Y[floor]);
        pi5 = n;
    }
    else if (pi1 != m && pi2 != m && pi3 != m && pi4 != m && pi5 != m && pi6 == m) {
        locateObject(p6, hanoi_tower, X[1][n], Y[floor]);
        pi6 = n;
    }
    g++;
    setTimer(timerMixing, animationTime);
    startTimer(timerMixing);
}

int main(void)
{
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    scene_create();
    object_create();

    hanoi(6, 1, 3, 2);
    startGame(start_scene);
}