#define AUTOMATIC_SIGNAL uCondition waitList
#define WAITUNTIL(pred, before, after) {\
        if(!(pred)) {\
            before;\
            while(!waitList.empty()) waitList.signal();\
            do { waitList.wait(); } while(!(pred));\
            after;\
        }\
}
#define RETURN(expr) {\
    while(!waitList.empty()) waitList.signal();\
    return (expr);\
}
