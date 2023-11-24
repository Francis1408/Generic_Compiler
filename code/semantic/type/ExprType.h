#ifndef EXPR_TYPE_H
#define EXPR_TYPE_H

class ExprType {
    public:
        enum Types {
            ERROR = -1,
            INTEGER,
            STRING,
            FLOAT,
        };

        ExprType(enum Types type);
        virtual ~ExprType();


    private:
        enum Types type;
};

#endif