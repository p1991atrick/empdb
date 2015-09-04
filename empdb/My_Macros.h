//
//  My_Macros.h
//  Personal #include file
//
//  Created by Gordon Freeman on 8/27/15.
//  Copyright © 2015 Patrick Kelly. All rights reserved.


//debug comments (T/F)
#define SHOW_DEBUG_OUTPUT 0

//array size calculation    total bytes/bytes of 0 location
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

//sort array #'s only. a=array  and b=size of the array
#define SORT_ARRAY_NUM(a)(b) {int swap, temp;                               \
                            do                                              \
                            {                                               \
                                swap = false;                               \
                                for (i = 0; i < (b - 1); i++)               \
                                {                                           \
                                    if (a[i] > a[i + 1])                    \
                                    {                                       \
                                        temp = a[i];                        \
                                        a[i] = a[i + 1];                    \
                                        a[i + 1] = temp;                    \
                                        swap = true;                        \
                                    }                                       \
                                }                                           \
                            } while (swap);                                 \
                            }