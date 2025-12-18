#ifndef TYPEENUMS_H
#define TYPEENUMS_H

#include <QObject>

class TypeEnums : public QObject
{
    Q_OBJECT
public:
    enum TypeObject {
        Hero,
        Brick,
        Tree,
        Spruce,
        Jug,
        Road,
        Food
    };

    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

};

#endif // TYPEENUMS_H
