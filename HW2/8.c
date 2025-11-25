#include <stdio.h>

int main(){
    double x1, y1, x2, y2, x3, y3;
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);

    int minx = x1;
    if(x2 < minx) minx = x2;
    if(x3 < minx) minx = x3;

    int maxx = x1;
    if(x2 > maxx) maxx = x2;
    if(x3 > maxx) maxx = x3;

    int miny = y1;
    if(y2 < miny) miny = y2;
    if(y3 < miny) miny = y3;

    int maxy = y1;
    if(y2 > maxy) maxy = y2;
    if(y3 > maxy) maxy = y3;


    double s = x1*y2 - x2*y1 + x3*y1 - x1*y3 + x2*y3 - x3*y2;

    int count = 0;
    for(int x = minx ; x <= maxx; x++){
        for(int y = miny ; y <= maxy; y++){
            double s1 = x*y2 - x2*y + x3*y - x*y3 + x2*y3 - x3*y2;
            double s2 = x1*y - x*y1 + x3*y1 - x1*y3 + x*y3 - x3*y;
            double s3 = x1*y2 - x2*y1 + x*y1 - x1*y + x2*y - x*y2;

            if(s1*s > 0 && s2*s > 0 && s3*s > 0){
                count++;
            }
        }
    }

    printf("%d", count);
    return 0;
}
