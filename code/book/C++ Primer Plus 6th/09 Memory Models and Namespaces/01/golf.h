#ifndef GOLF_H_
#define GOLF_H_

const int LEN = 32;
struct golf
{
    char full_name[LEN];
    int handicap;
};

void set_golf(golf& g, const char* name, int hc);
void set_golf(golf& g);

#endif // GOLF_H_
