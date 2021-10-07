#include <stdio.h>
#include <Windows.h>
#include "OpenCV/InitOpenCV.h"
#include "vector.h"
#include <vector>
#include<time.h>
using namespace std;

struct PARTICLE
{
    Vector2f   Pos;
    Vector2f   Dir;
    float      Speed;
    bool       life;
    int        MaxLifeTime;
    int        Lifetime;

};
Vector2f  Goal = Vector2f(0, 0);

void CallBackFunc(int event, int x, int y, int flags, void* userdata) 
{
    if(event == EVENT_LBUTTONDOWN)
    {
        Goal = Vector2f(x, y);
    }
}

int main()
{
    srand(time(NULL));
    vector<PARTICLE> m_Particle;
    m_Particle.clear();
    
    for(int i = 0; i<1000; i++)
    {
        PARTICLE a;
        a.Pos = Vector2f(0, 0);
        float r = (rand() % 360) / 180.0f * 3.14;
        a.Dir = Vector2f(sin(r), cos(r));
        a.Speed = rand() % 5 + 1;
        a.Lifetime = 0;
        a.MaxLifeTime = rand() % 20 + 1;
        a.life = true;
        m_Particle.push_back(a);
    }

    Vector2f Goal = Vector2f(0, 0);
    float count = 0;

    Mat map = imread("map.png");

    namedWindow("Particel", 1);
    setMouseCallback("particel", CallBackFunc, NULL);
    int time = 0;
    bool IsGoal = false;
    while (1)
    {
        Mat tmap = map.clone();

        float lenMax = 1000000;
        int id = 0;
        for (int i = 0; i < m_Particle.size(); i++) 
        {
            if (time % 50 == 0) 
            {
                float r = (rand() % 360) / 180.0f * 3.14;
                m_Particle[i].Dir = Vector2f(sin(r), cos(r));
                m_Particle[i].Speed = rand() % 5 + 1;
            }
            m_Particle[i].Pos += m_Particle[i].Dir * m_Particle[i].Speed;
            if (m_Particle[i].MaxLifeTime < m_Particle[i].Lifetime)
                m_Particle[i].life = false;

            if (m_Particle[i].Pos.x >= 0
                && m_Particle[i].Pos.x < 600
                && m_Particle[i].Pos.y >= 0
                && m_Particle[i].Pos.y < 600) 
            {
                int b = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[0];
                int g = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[1];
                int r = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[2];
                int p = b + g + r;

                if (p <= 0)
                    m_Particle[i].life = false;

                if (m_Particle[i].life == true)
                {
                    Vector2f pt = m_Particle[i].Pos - Goal;
                    float lpt = pt.Length();
                    if (lpt <= 10)
                        IsGoal = true;
                    if (lenMax >= lpt)
                    {
                        lenMax = lpt;
                        id = i;
                    }
                    circle(tmap, Point(m_Particle[i].Pos.x, m_Particle[i].Pos.y), 3, Scalar(0, 255, 0), -1);
                }

            }

            else
            {
                m_Particle[i].life = false;
            }
            m_Particle[i].Lifetime++;
        }

        for (int i = 0; i < m_Particle.size(); i++) 
        {
            if(m_Particle[i].life == false)
            {
                m_Particle[i].Pos = m_Particle[id].Pos;
                float r = (rand() % 360) / 180.0f * 3.14;
                m_Particle[i].Dir = Vector2f(sin(r), cos(r));
                m_Particle[i].Speed = rand() % 5 + 1;
                m_Particle[i].Lifetime = 0;
                m_Particle[i].MaxLifeTime = (rand() % 50 + 1);
                m_Particle[i].life = true;
            }
        }

        circle(tmap, Point(Goal.x, Goal.y), 10, Scalar(255, 0, 0), -1);

        char str[255];
        sprintf(str, "TIME: %d", time);
        string tex = str;
        putText(tmap, tex, Point(400, 30), 1, 2, Scalar(255, 0, 255));
        imshow("Particel", tmap);
        cvWaitKey(10);
        time++;
    }

    m_Particle.clear();
    return 0;



    /*for (int x = 0; x < map.cols; x += 1)
    {
        for (int y = 0; y < map.rows; y += 1)
        {
            int b = map.at<Vec3b>(y, x)[0];
            int g = map.at<Vec3b>(y, x)[1];
            int r = map.at<Vec3b>(y, x)[2];
            if (r > g && r > b)
            {
                Goal += Vector2f(x, y);
                count++;
            }

        }
        Goal /= count;

        Mat map = imread("map.png");

        namedWindow("Particel", 1);
        setMouseCallback("particel", CallBackFunc, NULL);
        int time = 0;
        bool IsGoal = false;
        while (1)
        {
            Mat tmap = map.clone();

            int id = 0;
            float lenMax = 1000000;

            for (int i = 0; i < m_Particle.size(); i++)
            {
                if (time % 50 == 0)
                {
                    float r = (rand() % 360) / 180.0f * 3.14;
                    m_Particle[i].Dir = Vector2f(sin(r), cos(r));
                    m_Particle[i].Speed = rand() % 5 + 1;
                }
                m_Particle[i].Pos +=
                    m_Particle[i].Dir * m_Particle[i].Speed;
                Vector2f pt = m_Particle[i].Pos - Goal;
                if (pt.Length() <= 10)
                    IsGoal = true;

                if (m_Particle[i].Pos.x >= 0 &&
                    m_Particle[i].Pos.x < 600 &&
                    m_Particle[i].Pos.y >= 0 &&
                    m_Particle[i].Pos.y < 600)
                {
                    int b = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[0];
                    int g = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[1];
                    int r = map.at<Vec3b>(m_Particle[i].Pos.y, m_Particle[i].Pos.x)[2];
                    int p = b + g + r;
                    if (p <= 0)
                        m_Particle[i].life = false;

                    if (m_Particle[i].life == true) 
                    {
                        float lpt = pt.Length();
                        if (lpt <= 10)
                            IsGoal = true;
                        if (lenMax >= lpt) 
                        {
                            lenMax >= lpt;
                            id = i;
                        }
                    }
                        circle(tmap, Point(m_Particle[i].Pos.x, m_Particle[i].Pos.y), 3, Scalar(0, 255, 0), -1);
                }
                else
                {
                    m_Particle[i].life = false;
                }
                if (m_Particle[i].life == false)
                {
                    m_Particle[i].Pos = m_Particle[id].Pos;
                    float r = (rand() % 360) / 180.0f * 3.14;
                    m_Particle[i].Dir = Vector2f(sin(r), cos(r));
                    m_Particle[i].Speed = rand() % 5 + 1;
                    m_Particle[i].life = true;
                }
            }
            circle(tmap, Point(Goal.x, Goal.y), 10, Scalar(255, 0, 0), -1);

            char str[255];
            sprintf(str, "TIME: %d", time);
            string tex = str;
            putText(tmap, tex, Point(400, 30), 1, 2, Scalar(255, 0, 255));
            imshow("Particle", tmap);
            cvWaitKey(10);
            if (IsGoal == true)
                cvWaitKey(100000000);
            time++;
        }
        return 0;
    }*/

}
