//
// Created by matejko on 25.2.2017.
//

#ifndef ROBOT_DEMO_TYPES_H
#define ROBOT_DEMO_TYPES_H

struct Velocity{
public:
    double linear;
    double angular;
    Velocity() : linear(0),angular(0){

    }
    Velocity(double linear, double angular) : linear(linear), angular(angular){

    }
};

struct Position2d{
public:
    double x;
    double y;
    double yaw;
    Velocity vel;
    Position2d() : x(0),y(0), yaw(0),vel(Velocity(0,0)){

    }

    Position2d(double x, double y,double yaw, Velocity vel) : x(x), y(y), yaw(yaw),vel(vel){

    }
    Position2d(double x, double y,double yaw) : x(x), y(y), yaw(yaw),vel(0,0){

    }
};

struct Command
{

    enum CommandType {
        Motors, Radius, LinearAngular
    };

    double linear;
    double angular;
    double leftVel;
    double rightVel;
    double radius;
    CommandType commandType;

    Command() : linear(0.0), angular(0.0), leftVel(0), rightVel(0), radius(0), commandType(Command::Motors) {}
};


#endif //ROBOT_DEMO_TYPES_H
