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
pcAh3lbLJktYI3uhaVGyVhTtrpSrPUMs6xaoaJsaw2FZ0C6XWHgb2jrnjbE3hdhF2VbZlPw7R/bEPQdZIyvouTH4cQ+WTAllw5WfTMJ5AlduFLlBcg3hObjB9Rbvwg/GqA2BURvg9+uGK2TRgFitK8HzveA/tNMtJ5nAaB5Nw1mSXnjeLI29YIxJp2GQelEURnAMvaMjiPmaRP5LD3qVWJIK4I3z86FzgBv0lHKmNqnims4bvygthejxBAL30rO+HWLxGv7kGEDxOhf1DVWQs6bawCRJZqhjtUY0Dmfv4fjgwIDG10E4i/3Y+knUWdXmHE6JRSfP8swyATOJ+8/J9ekNvCpROBXq55vEbOv/R0UlkSixTresByeG2diLR5E/S/wwsNzOCpuPrThKCxM0zXCIOqsqZUSG1WxYs6HtvRrQu4b/1XKlYSnzjSU6UZqSmMwarlHLNBkUoCGrCANFUzHsK5IzqhDr1XV4zgvWVjh8Mjoa686MiSUnF4VleQxL/ZRVEqtNwVDUnK0INJN1zY2vY1lG/t0hU3DVCm3mRIGGK1YTlSCZXgJrEaTWImNkaoNwuAOYBxJja1R2t2/lEju7lpqGBCwKf3cmlKo7Tyb948GimNmA7YVTUGnOcqqkwh7DALIRfxucd11Q
*/