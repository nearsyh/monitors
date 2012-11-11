#define AUTOMATIC_SIGNAL uCondition waitList
#define WAITUNTIL(pred, before, after) (\
        before\
        if(!pred) waitList.wait();\
        waitList.signal();\
        after)
#define RETURN(expr) return expr;
