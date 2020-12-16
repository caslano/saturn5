//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593
#define BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //BOOST_THROW_EXCEPTION(
    //    bad_type() <<
    //    errinfo_type_info_name(typeid(x).name()) );
    typedef error_info<struct errinfo_type_info_name_,std::string> errinfo_type_info_name;
    }

#endif

/* errinfo_type_info_name.hpp
vDxqeL7GTv4lp2yy+5fcdV+B/mAGZaVca24pzB9m20Z7eWV3DMUfJp6Vv3rlUPLPysp//8ND8KfxUXbN+26VzD04vcn/cwMzXZS1qauuCBjSw/kwzBCED5fg6qDgtzP+WVHofg17eR/fkMffdI5Sp+ZC73cugKpdvUHx68f/CkwIznDni+0qZ8GX+dybyLHVJ8LRjhB0Cgbd8oYI+hQFhTCok4KupqBqDGp9Q7yX4fud+L7F8/pfAPygl3rmGa8X9unjtZEZipnY5ZcHDG1VPt8oW4ItkDpR7l+oIsXr3YOMuKf/vWLwbS3/Ze9IoKMqkjNDhgxJIMMRCIcQJEA41HAICaBOMOKgYQkIGgSXeCBRUQMkEFgOIaBADIKC4qIu6q6K6wGKGA4xqEBYPADXY1dd7+TH8UBcFRTNVnV11/T/M5P8JLh33lPmd3dd3dVXdXW1HXlE+60vt9N+3/0s269OfBeWh9G/728M0b82Tql+HmPPUal9dvgNPG+H36vr0Lc/EJYyr7TuAY93zIXjmjincdEmyAKzTCeMdwFpsGB9WGzZE76mr7vhy8bDsBH47/O81f8yvFaQGvg0NfArNfAJNRj6ta0+q9362LSLSAfdZ+5ySnMezIPktxIjPqsXQIbR/0H9UpO0x59C9vgvbkZDd3M0dE9hQ/evHxX2+AzGyrNrqnThykUtX3C++ImiZWzrKfC57wV8YAqkDBTv+SXKfKe/v57IxrzH9CuFuVCJy/1t9G+vfKw9l9zhYM9zGk2nA4CSIuMxeixXOx/9YXd6MRiHIb8oSlF0M8pSCcWRpYzCY3yyjDD4zS/Ko0EQEUSL5EAqjeZT1gjntKRBVIsPLyUHNlMtJm7EWvxXXebgq85BlS3aqQbnV6twcG4NvWWtG/0h6NLSNkiFzM3wD6nVR3SY8AiXvgtLv0Cl76DSJVx6i9i5XktV+/gycFaME8byRXoELiq6XO3LROQCj/oJLRalfmdj68m7iElAw9jRFM3F+PLeDCJxAZCgex73HsKaDgxS5Y9VQvkSKi9vjDV/F9Pofknzt/H3H+E3dP8GX3C0U/8h/k/blX/SK03YPykunP/TLVUN8n9i/JdFMX5POP+nOvFr9yl54Bks0Ze4e+xqG3xpU1te5tIwc9b1n+IStJ86bZoMn0YHYIm3SfMSSuhqUCZmjXbrpicRMK03NfLSxS2lsemPMHVZQ3sMoKtV5FmSR5eCRkZRr82Xyfky2SOvtPN7nAP2VTXiPU478UGit6n6+m4n15d4lz9NjMfs6SKvSA5Ddsl8c9aAT7AGhyoLXXf4NN4GSz1PL/O6SG2Pwazmsr1TEXuqZpTDuuxJdZlerOry+Z9CDXed5d21lnKF4qAB2LHcydXmx2o7seekVBvN358+KxU2IUvQaH7mxyDMKpe4k9wdfjsouQcmt6fkth/bWfppa/GbiEhG2SKqh5ZLaOBINa56hRfl4ed73jRieS+ZdOrcP4iuGPusnfXNnTV1r8ckfWQZUoAH5qK2+10lW5m+flcMugfc3eJoVQXuErB7JYaW8sCutg8FH7K3Huq41Y68F9uQV+7/nrHuv3avsLnfXEWgBLVqRZ33q3L18i0W29uf9gnhL+OP9dlfBrZY4T9bY1O+TQRKUE9GgLKQm0cwQWqX7qljP1rqngArrBe17zlLzd9/WWL+Pm4pf02x+Xv/IvP3yEUW+GWW/MWWfMZnif/yNF3KyYI9N79Ntm1WnfKZ+CVU4yUqp0BVYbj2M5Za7n9JoPL9Gv10pl/r+PcUgS7dT/Rur7BBb5ME2r9Yo7e/0A69Qgm6cjHRO9UOPZ8E+sNzGr0JhXXWb6/Q+v12M6G69Dk=
*/