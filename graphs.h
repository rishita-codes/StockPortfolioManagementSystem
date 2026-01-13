#include<stdio.h>
#include<math.h>
/*
Structure: data
----------------------
Represents graph data
label: name of value to be represented on x-axis
y: the label's corresponding value on y-axis
*/
typedef struct data{
    char label[16];
    double y;
}data;
/*
Function: graphical
----------------------
Plots a graph to the console
Parameters:
    d: d is an array of data which stores the dataset to draw the graph from
    n: n is the number of observations in dataset
Returns: void
*/
void graphical(data* d, int n)
{
    int i, j, c=n, k, f[n]; // f is an array of flags
    for(j=0;j<n;j++)
        f[j]=0;
    d[0].y=round(d[0].y*100)/100; // round off the number to 2 decimal places
    double max=d[0].y, min=d[0].y, jump, step;
    // finds the max and min value to be plotted on y-axis
    for(i=1;i<n;i++)
    {
        d[i].y=round(d[i].y*100)/100;
        if(d[i].y>max)
            max=d[i].y;
        if(d[i].y<min)
            min=d[i].y;
    }
    jump=(max-min)/(n-1); // the scale for y-axis
    step=max+jump; // the highest step of y-axis
    printf("  PRICE IN|\n");
    printf("%11s%30sSCALE: %.2lf\n","INR  |","",jump);
    printf("%10.2lf|\n",step);
    for(i=n; i>0; i--)
    {
        step=step-jump;
        printf("%10.2lf|",step);
        for(j=0;j<n;j++)
        {
            // rounding off to nearest step
            if(d[j].y==step || d[j].y>step && d[j].y<(step+step+jump)/2 || d[j].y<step && d[j].y>(step+step-jump)/2)
            {
                printf("%3s","*");
                f[j]=1; // records that jth data has been plotted
            }
            else
            {
                if(f[j]==1)
                    printf("%3s","|"); 
                else
                    printf("%3s","");
            }
        }
        puts("");
    }
    printf("%11s","+");
    puts("-------------------------------------------------------------------------------------------------------");
    printf("%11s","DAY ");
    for(i=0;i<n;i++)
        printf("%3s",d[i].label);
    puts("\n");
}