//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright Christopher Brown 2013

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

#include <boost/chrono/config.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <cassert>
#include <boost/assert.hpp>

# include <pthread.h>
# include <mach/thread_act.h>

namespace boost { namespace chrono {

    thread_clock::time_point thread_clock::now( ) BOOST_NOEXCEPT
    {
        // get the thread port (borrowing pthread's reference)
        mach_port_t port = pthread_mach_thread_np(pthread_self());

        // get the thread info
        thread_basic_info_data_t info;
        mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
        if ( thread_info(port, THREAD_BASIC_INFO, (thread_info_t)&info, &count) != KERN_SUCCESS )
        {
            BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
            return time_point();
        }

        // convert to nanoseconds
        duration user = duration(
                static_cast<thread_clock::rep>( info.user_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>(info.user_time.microseconds ) * 1000);

        duration system = duration(
                static_cast<thread_clock::rep>( info.system_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>( info.system_time.microseconds ) * 1000);

        return time_point( user + system );
    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    thread_clock::time_point thread_clock::now( system::error_code & ec )
    {
        // get the thread port (borrowing pthread's reference)
        mach_port_t port = pthread_mach_thread_np(pthread_self());

        // get the thread info
        thread_basic_info_data_t info;
        mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
        if ( thread_info(port, THREAD_BASIC_INFO, (thread_info_t)&info, &count) != KERN_SUCCESS )
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                EINVAL,
                                ::boost::system::system_category(),
                                "chrono::thread_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }

        // convert to nanoseconds
        duration user = duration(
                static_cast<thread_clock::rep>( info.user_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>(info.user_time.microseconds ) * 1000);

        duration system = duration(
                static_cast<thread_clock::rep>( info.system_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>( info.system_time.microseconds ) * 1000);

        return time_point( user + system );
    }
#endif
} }

/* thread_clock.hpp
JUn81u95xz71/S387VPr97T0Ckq2HXA14dZQZ1e4xausRGpnWT6MV1/fP5+J/yk7rR3jN9Xrcx4Q/5OWWrsk8AvZfy/vJ3f6Cy112nGgIfdBW1xjY33vtJOwlrb3zi7mgXXEe9J3rqFYOUZ1+qFQF3+EXjf0U3mW976nzn6OnBLXCWX9otx87o1f6f+d/gaSP6Xq8V4ZstX/+yXnxElWss3hGr43wSUgTZpLZ2k+MWRPzs/PmVAg94m0gTh5XijQ35Muk7h5bBNMi7Ky+mZS1+qbCe+dayRdPYmXqkp8F+rl7o9au/sjllOc61uIWW5yLkP8cn4zTI5bXsJwbpblgM98v3mMpL9aUPN4XjSPN0ea4cOO3x7aaei8op2Vu1VetuuT6L+n5rG5heaxiDrHleb3Fv7duAy+R/LvkWWof9R2HBzHQq/VqIwpZ5K0oj8bDDYCrwIbg1eAzeinDoo2F5S5hQ6qIuIlgPXA8mAVsAp4AdgHrA9eTv+V9DOfsEnY6yDvp27sAerk5lAH+TCYTt1gP/qpg4R9wE4HSf0Vtnuog7zXW4+58/zpIMPd39r53b41x/qd4vHWI14N6tvqcR6cptTrdab+Lp/6u5s4r83NfmsILqGO9VfwMPg7/SGGy1/WcPnLcb6bePBrsBLnvalBfy3wG7AOeAxsyPlwmoDHwWacF6cl+E+wNefHaQeeAi8HfwcHgYahZjwCOsBFYLThpZfk999uFrrF5dRL/oPluYJ6ybXUMa6kXvJVtoPXuHbm69TbraZucg3bxVrWw0AHv3nymy3OK3Xdm7bI2Yar3h4H64JPgkPAxVwD9AWuAboEHA++yPlTloKTwZcMV/0UgreBr4D3mNcD3mdeDzjHzC/4ELgKnG/mF3wcXAc+DVZ0uPSnlcAPwTTwYzAF3EP/PrApeARsDn4DtgC/BVs6qKsET4JtwH+DbUHUgWoHxoPtwZpgR7Au2AlMA7s6XPV6MdgW7Ab2BC8BLwV7gzIHM3gVeAX4LDgAXA5eCa4Es8DVYB54HLwGDEFZF4Ax4BSwGXi7eT7wfrADOB/sAr4A9gCXgn3BDeAVYJF5XvA9MBPcCo4At4FjwR3gBPATMA/cDV4PfgbOBH8xyxcs44SuFzwGP9KqaPiRRsWAX4Cx4H4wHjwIJoBfgeXBo2Ay+A1Y0cn2peR7jk+/GA729pqnJh58ju36ebbrl9muF7PdLgUv45rEA7hfzyPE5/HWFvMIjeHaq7lgPfA+6tivAZuJn/236ZjPjhb996PM53zeZwvA+pyPJ4066+bUWbdhOHW8+IZgr+NNcbryV83pSlcDbA+msvxw/XzvRVz2k/FyftlkDeEaYANe34VgK7AJaJZNU7AP2Ay81CwX3qetwIVgW3Ap1/xdz7V+t4IdwO1c87eYa/weBTuxvC42XPfPJWCo2WcYXvO4sT6mWvxexbI+4jkfU3nDVc+VwJFgZXASWMcz3xLfU9CGLeZb6oV4NbnmcH2uOSzaabAD1xzuB/YDrwIHgTeDQ8HZYCY4FxwGPglmsTyGgyvBkbp98FkcnGPRPoaWgZ7ajA82BEeB5jWPA/uC48twninwJvBaM14pdM7bNrs0zifA8KKIAK1zSlHEedM7Ny+KOGfNs2oeKrrn7kUR/5fa5w0TS163cBiu204DXYB9C+A2wO2DU+9GqGS4dLghcFPh5sKtgfsY7gRc1Huoc7iM94Ka6OAW3IJbcAtuwS24Bbfgdu7bnzT/X/bECRPOef0/t/Z/9nNe2n85dE52QZ5L+7+0vKI+GvEMj548gfyxslJ5G7U+usulffte3KW/KFTEHvN9ZdGnaHvMHRL3Utpj3GmTtA3zE/E=
*/