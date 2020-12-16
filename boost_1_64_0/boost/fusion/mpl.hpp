/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_09172006_2049)
#define FUSION_MPL_09172006_2049

// The fusion <--> MPL link headers
#include <boost/fusion/iterator/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>

#include <boost/fusion/mpl/at.hpp>
#include <boost/fusion/mpl/back.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/clear.hpp>
#include <boost/fusion/mpl/empty.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/mpl/erase.hpp>
#include <boost/fusion/mpl/erase_key.hpp>
#include <boost/fusion/mpl/front.hpp>
#include <boost/fusion/mpl/has_key.hpp>
#include <boost/fusion/mpl/insert.hpp>
#include <boost/fusion/mpl/insert_range.hpp>
#include <boost/fusion/mpl/pop_back.hpp>
#include <boost/fusion/mpl/pop_front.hpp>
#include <boost/fusion/mpl/push_back.hpp>
#include <boost/fusion/mpl/push_front.hpp>
#include <boost/fusion/mpl/size.hpp>

#endif

/* mpl.hpp
bP1hyrW6iTKNe+qJ8fF8mlj7WGfNOds2ac6vBmnOv6RzPZ5L0qAXZP6uvknpg9h5+KauXYp9byWxH3uPRRr0Gm9i/KUzf+Lf4qqKrwfYhP+lJsrYc/oE3cT+ivj/KmPvD/2H512xtVzpvG8lMS75fI6/2yD+zCPZcWQTckC6cd8gjTiOP3eKr6f+hzXHaX4TaFPn37J1OT323Of7rxFOt3+y+ngMx5+Hxa8B42tnUr6nIP78PsV9nZTXGhu+F3p8yjV1ibrYPYeEreN5PB6vsfPX+HxN/o2s+JqVxHunU3/3On6tndhPxGXtf0zX+jOdnBTrl/x7fIkcsf77BjLkjsQz78RhL3bPP9W7p+NzIrGfun9C9w2/7bZ0/ftBG/vOUFXivQ3J8kdV7NtfSb5v22rQFoO6Dci8vllx7H8CsW9lxZ4fp/quZ8LP8XeiJHnWtO44lCpfJuyW6nog/u7y2Hneitr7Xon13Y2VTepETcL4lnWilqFfkGmbOtE2f3+veKJv2N+2TrRtVaJcFSvj7cvW7W8bSjwOObzzGvrf7tI5qtq1czT/jTXlWjvUqxvV61+3eA2vZbUyrFfWrxPVD+V2W0Tbrai3dKtEoCT0Tcj4Hcpa2XeoE+1QK/t69Y1C/bJ1slfu3jl6E64je+2vVvZGQdaqdX1fWdI52maPztETSfqm+h7atqFcj9+pxv9oqfFvJspaGiVo1MZrM/un1c1el9MS+mUGPbaItvXm+LpL16tf3171t4jq17kz2mpNe8yHtXZalsx+CTrbbRltN3DraLv+a/8J23GrutFW+9SLVh7SOfoaLprRO1pTH0WxutRjxxzaOZoHr6wbG69bp1+0+bf5t/m3+bf5t/m3+bf5t/m3+bf5t/m3+bf5t/m3+bf5t/m3+bf5l/6v9ches0J5yXZZa+4vPrbjWpy9uHf0xFW9o23e7x1t18w7kUd5J7SHOvXLo2h6ThT9zHavwvBulij6eYsoOi0ripq3tCa2JIoGjIyiFV2iqNCDk/30+bH9q92s/agyip5397OTe6pZQ9Fpat3pWLz1faI0im4b7D6y9mZoPdonih5p7p6wdw1tvSCKdjJ+B/0aKU9uocSrkuSn9Iyie3pFUYu2ZCbbqE5R9JtC9PCusZ1pzDZkPbqKLIui6MmMKHp8RBT9St+H0Tkzg05oXqs8ZG4U/blrFN00Dc3h5OkXRSeQ4ST3XosnRdFlE6PowPZRNHaSPiPxwfM6dQfY3wreQPeUGVE0Yacouqs4itqz2dDu+g2KoiGd6ZOBL5qFo6Po9T50g8tn6d/G/4xtnz1YfzJPahVFs6eThdw/0t6DPRqi8zD5M4qiqMGUKPqqSRTtOC6KBlWhjXdWhyg6uJCOdOqD9562e+l/Kr71J0TRccbtzzfd0f0p+u9NVt8uiq4i/6Wto+jrQrqSI9LenIx/MO5xer9o+0rb3/LXm9l8PYiMQ/hT/Wlk/WYgn40ip/2j7D84je/ExGvz8GvEBj34ZpCxfFQnh737siP+HdFaMkdMueG93G3unmPQ0va+ui20PUuPi6bTy/jnoTucrV/XmfS13YjszbqzC54ZZVG00PiJ5Pg1mV8QUzfWsO0IduxjPHnasvkn2ga1pY+6seoOxqezvtPJ/HlBFD01VH/jDhOXvfnwafLezc478cuyqVHUpDndwlyowXesffH8y3HsTNYRnkc8x379tUXqptD/ZrHXoT89WrPPAn6h9znqu9v/uAPdGpLHfg09islznv3b+XOPpnjiO1W5o7lyFp5vstMKtr6kJx+X8oP9HezXDfNirjFoD62IovNzyA9fzEdzFHr6zsX7wkr1E9mIjkXk2tX23rY=
*/