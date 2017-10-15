#include <iostream>
#include "Player.h"
#include "Arena.h"
#include "Globals.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

string Player::takeComputerChosenTurn()
{
    if(m_arena->nRobotsAt(m_row,m_col+1)==0 && m_arena->nRobotsAt(m_row,m_col-1)==0 && m_arena->nRobotsAt(m_row+1,m_col)== 0 && m_arena->nRobotsAt(m_row-1,m_col)==0) //IF NOT SURROUNDED
    {
        if (m_arena->nRobotsAt(m_row, m_col + 2) > 0 || m_arena->nRobotsAt(m_row, m_col - 2) > 0 || m_arena->nRobotsAt(m_row + 2, m_col) > 0 || m_arena->nRobotsAt(m_row - 2, m_col) > 0)
        {
            if (m_arena->nRobotsAt(m_row, m_col + 2) > 0) //IF THERES A ROBOT 2 SPACES TO RIGHT
            {
                bool status = shoot(RIGHT);
                if (status == true)
                {
                    return "Shot and hit!";
                }
                else
                {
                    return "Shot and missed!";
                }
            }
            if (m_arena->nRobotsAt(m_row, m_col - 2) > 0) //IF THERES A ROBOT 2 SPACES TO LEFT
            {
                bool status = shoot(LEFT);
                if (status == true)
                {
                    return "Shot and hit!";
                }
                else
                {
                    return "Shot and missed!";
                }
            }
            if (m_arena->nRobotsAt(m_row + 2, m_col) > 0) //IF THERES A ROBOT 2 SPACES DOWN
            {
                bool status = shoot(DOWN);
                if (status == true)
                {
                    return "Shot and hit!";
                }
                else
                {
                    return "Shot and missed!";
                }
            }
            if (m_arena->nRobotsAt(m_row - 2, m_col) > 0) //IF THERES A ROBOT 2 SPACES UP
            {
                bool status = shoot(UP);
                if (status == true)
                {
                    return "Shot and hit!";
                }
                else
                {
                    return "Shot and missed!";
                }
            }
        }
        else
        {
            stand();
            return "Stood.";
        }
    }
    else ////////////MOVER FUNCTIONS//////////////////
    {
        if (m_arena->nRobotsAt(m_row + 1, m_col) == 0) //IF THERES NO ROBOT 1 SPACE UP, MOVE
        {
            move(DOWN);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row - 1, m_col) == 0) //IF THERES NO ROBOT 1 SPACE UP, MOVE
        {
            move(UP);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col + 1) == 0) //IF THERES NO ROBOT 1 SPACE RIGHT, MOVE
        {
            move(RIGHT);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col - 1) == 0) //IF THERES NO ROBOT 1 SPACE LEFT, MOVE
        {
            move(LEFT);
            return "Moved.";
        }
    }
    stand();
    return "Stood.";
}
void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    switch (dir)
    {
        case UP:
            if (m_row > 1 && m_row <= m_arena->rows())
            {
                m_row-=1;
                m_age++;
                break;
            }
            stand();
            break;
        case DOWN:
            if (m_row >= 1 && m_row < m_arena->rows())
            {
                m_row+=1;
                m_age++;
                break;
            }
            stand();
            break;
        case LEFT:
            if (m_col > 1 && m_col <= m_arena->cols())
            {
                m_col-=1;
                m_age++;
                break;
            }
            stand();
            break;
        case RIGHT:
            if (m_col >= 1 && m_col < m_arena->cols())
            {
                m_col+=1;
                m_age++;
                break;
            }
            stand();
            break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;
    
    if (rand() % 3 == 0) // miss with 1/3 probability
    {
        return false;
    }
    else if (dir == UP)
    {
            for (int i = 0; i < MAXSHOTLEN + 1; i++)
            {
                if (m_arena->nRobotsAt(m_row - i, m_col) > 0 && m_row - i > 0)
                {
                    m_arena->damageRobotAt(m_row - i, m_col);
                    return true;
                }
            }
        
    }
    else if (dir == DOWN)
    {
        for (int i = 0; i < MAXSHOTLEN + 1; i++)
        {
            if (m_arena->nRobotsAt(m_row + i, m_col) > 0 && m_row + i > 0)
            {
                m_arena->damageRobotAt(m_row + i, m_col);
                return true;
            }
        }
        
    }
    else if (dir == LEFT)
    {
        for (int i = 0; i < MAXSHOTLEN + 1; i++)
        {
            if (m_arena->nRobotsAt(m_row, m_col - i) > 0 && m_col - i > 0)
            {
                m_arena->damageRobotAt(m_row, m_col - i);
                return true;
            }
        }
    }
    else if (dir == RIGHT)
    {
        for (int i = 0; i < MAXSHOTLEN + 1; i++)
        {
            if (m_arena->nRobotsAt(m_row, m_col + i) > 0 && m_col + i > 0)
            {
                m_arena->damageRobotAt(m_row, m_col + i);
                return true;
            }
        }
    }
        return false;
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}
