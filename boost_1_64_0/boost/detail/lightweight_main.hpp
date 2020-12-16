//  boost/detail/lightweight_main.hpp  -------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <exception>

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                exception reporting main() that calls cpp_main()                      //
//                                                                                      //
//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  try
  {
    return cpp_main(argc, argv);
  }

  catch (const std::exception& ex)
  {
    std::cout
    << "\nERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR\n"
    << "\n****************************** std::exception *****************************\n"
    << ex.what()
    << "\n***************************************************************************\n"
    << std::endl;
  }
  return 1;
}

/* lightweight_main.hpp
ZsIdW+iYhxdXYgLxpwPQJMgHj7TNlTLE8Za8zesYMJjypH6kUyp/BaibTWnnn8Lyp2eEbhKOBkfcwLGrWvpAH36AbKDiWpLPYfzEflVpdlNvE0p+sylJ/LozH7AfDthXSuz7Cew3Shhc23t7J2GvkpdVPpCuRFrcJuwjyxtZqNkH0+gdu9Vi3If2PEp3Q6WAA9FIxppEOw8RB/HiTtjj5lnll1Cr628VFzG/gcFnhB01XbKOxNmtXd2G5b9vM/WksiP0JKv8cgI3EsHt135qqGpveBdyqQvdrbpwZyaDXqJAz2HQ5UWol7vl9UOC9gVgowmYtgCAlRqBZWXCbesYQmkvK0H7cBrrYaANdI8DVbs3vzWpwOxy+Hq0ExqsJuNw/0UDM5uddNIrRqJOOtVehwXhf/xjlgc2DJJPPQSHvscIT/Hd3mT2wmcNNW923ZSpy8VkZs3sqMjQz389kZHFS68SfGEMHQLf7HC0Rnn79Q7SzFQUS9a7VnJL4x6n88hraP0B7pGPDUQaIE5eOJSAyXESurf4k9F5VRfzLnEdranLWcmqvfOV9v52GbV3Zwfr9j5uWbf2zFZ4B7xKfLqruL7WEyrUuEeb6RShxj+XocbVeEw40Plor8Z4YBcNZDHq6WZFBDYL36VEnJRopFTK/quvXYnLOBOq76QrzJb9LK4wAdaQUcZVCWXThXSV8MA8eX85WbLGsW7kKq2yo1fdd3B5KGEMpJt7dUFRoWPViRN0TljC460h/GIj/BXdzqyE9loY8i6ejxMvMr6/n9oPIto2MXh3ls0FjAHZigUS4y+7hv/+vmk5WPUXw0uGqk0mytCN8bvyIj+cK+3i+RyZiQ+54CJeESXuD+Xr/KhAOlHoVh7G3TsHujELuvGE7EZL6kYG6Zuw+LtUfDkWv9FY/EiXP0JPptBm7oVIm1BnBx9aW/RxKJGulPThDvWoDLHYUvhJM2pWA/y2zxYFUD28QKQs4JAFHFCgpXwMJJkXiJQFImEkrmGT4GRIurRogWQmIinTWzpUpQc+Y2GN5BOGpy7n9AbGTPZb43MyVNxarEBlEqIi08ezdPUtCw/K/p3wl2zBTS1YNhtI5mXtsizy6XRcbLCCXVY4oyxzWp9sK//uegOQ80DmkwpYCoBi97cmjvGJYP65sJu06S2NekcFvMH5HzWV+b0ohOMjNLP6zoSZtQxm1mI5s5Z1xpmViHBgIzmN8BGq/u8C7JXu6JuwYDOq8y+kLfH1EdbuwIhvO77+3SKFhXv19e9cxPcmuf7RAFNsrkfP51Dh0MjdY7GgoqmA0nLZ3ZV6tGZ7E/T1F1XVKgEeuHLAr+E8h1brRxETErMUe+WZ8WG9B/qhxxSPoWJo2PG813qU9mLDa2+yub1BQ8OK/+Dh8R9SeGnL/nvU/seFF8/ig/5m+/D3W9YhnsWq/qb+3OwLpz/XUDWt/cn64+mv9GdjbHj9aRDUn1bd6xJf4kC/oPgXLepAjzv6mehx3SXh0OMyqqY1aXISeqRTIYKb3piXtIQXxeHtTT5Z/JO+CrycBuHRd0PfoPgnZ9WBPpP7mvl/CK9dB/0Yf/+sr6KZPeylNbBtBmytTf0dlUith6bBmncPrHkz5JpX7Ua1Esiu3I23EUFqdpbUyU7MISd+tImmXPd5wqNEhF7G5Ae7B4ck7wjyXJEkVIGWdRaJc7Jepraztc12Ro5pYdDrh97S0j+X693+SgR6ulAG4rhZEujQ2UigRfB9Tuvgx7inKs+84jaJw+nsLDfKYWBpXXzYw37GCtOUR9lpEJLb2XxI5WbZPEQjgPBRmTbD8ORhjOnXKuX0Q09ZnS9xY32vlxRUvWTht8YPFFkOFMk=
*/