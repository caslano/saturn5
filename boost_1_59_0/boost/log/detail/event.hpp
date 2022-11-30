/*
 *          Copyright Andrey Semashev 2007 - 2021.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   detail/event.hpp
 * \author Andrey Semashev
 * \date   24.07.2011
 */

#ifndef BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#include <boost/atomic/capabilities.hpp>

#if BOOST_ATOMIC_HAS_NATIVE_INT32_WAIT_NOTIFY == 2
#include <boost/cstdint.hpp>
#include <boost/atomic/atomic.hpp>
#define BOOST_LOG_EVENT_USE_ATOMIC
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD) && defined(_POSIX_SEMAPHORES) && _POSIX_SEMAPHORES > 0 && BOOST_ATOMIC_FLAG_LOCK_FREE == 2
#include <semaphore.h>
#include <boost/cstdint.hpp>
#include <boost/atomic/atomic_flag.hpp>
#define BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE
#elif defined(BOOST_THREAD_PLATFORM_WIN32)
#include <boost/cstdint.hpp>
#include <boost/atomic/atomic.hpp>
#define BOOST_LOG_EVENT_USE_WINAPI
#else
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#define BOOST_LOG_EVENT_USE_BOOST_CONDITION_VARIABLE
#endif

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

#if defined(BOOST_LOG_EVENT_USE_ATOMIC)

class atomic_based_event
{
private:
    boost::atomic< boost::uint32_t > m_state;

public:
    //! Default constructor
    atomic_based_event() : m_state(0u) {}

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(atomic_based_event(atomic_based_event const&))
    BOOST_DELETED_FUNCTION(atomic_based_event& operator= (atomic_based_event const&))
};

typedef atomic_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE)

class sem_based_event
{
private:
    boost::atomic_flag m_state;
    sem_t m_semaphore;

public:
    //! Default constructor
    BOOST_LOG_API sem_based_event();
    //! Destructor
    BOOST_LOG_API ~sem_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(sem_based_event(sem_based_event const&))
    BOOST_DELETED_FUNCTION(sem_based_event& operator= (sem_based_event const&))
};

typedef sem_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_WINAPI)

class winapi_based_event
{
private:
    boost::atomic< boost::uint32_t > m_state;
    void* m_event;

public:
    //! Default constructor
    BOOST_LOG_API winapi_based_event();
    //! Destructor
    BOOST_LOG_API ~winapi_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(winapi_based_event(winapi_based_event const&))
    BOOST_DELETED_FUNCTION(winapi_based_event& operator= (winapi_based_event const&))
};

typedef winapi_based_event event;

#else

class generic_event
{
private:
    boost::mutex m_mutex;
    boost::condition_variable m_cond;
    bool m_state;

public:
    //! Default constructor
    BOOST_LOG_API generic_event();
    //! Destructor
    BOOST_LOG_API ~generic_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(generic_event(generic_event const&))
    BOOST_DELETED_FUNCTION(generic_event& operator= (generic_event const&))
};

typedef generic_event event;

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

/* event.hpp
YTFcwh6nnaV/zQ3JxljzY5mINXHCnX6moDrml11lLpvUCEAmZY05J9COaWG/iHy67Ql9pe01nPqzK1Y71DAJU+G9QXZ8jwgcwmAhetEO69/61SYhF2FPKnojWynGdhyp5bgVSBSOF/9SYota5UrJKi6kSw+KrURMJH09milEhX+RLdFs4JybomTXbAOYF4WqZZ0RcbpU8q+nUa1QDiP06ESNz9tVtKoPPtPBNd4L4a0u2v+o+4I8bc8cXwiUR+msjsFmhyWx/sQo7wcmTBOcE1WaA+M/UpWk1jtVaBxQtQXnWNpmjP3B+2uKnQ09wE2J2Ri0rGNzAwzAG5TFnSkyK45EKbT1FEIIfH4yCndS7+GXlUsTtz+mwvlzHBhDWPBTAaX4JfisPNuH5QnS06PUZtfTdV31MczGJGf6s4WOdO615hVEb9+nrXexHen4jVYxxMgsDHBJHgjm1raVJHcE15xffzw+52FdWwIFgs7fklaTReFeWFQ872FAKSxkm1gsZTgYheSvKvnPTFE8J7VpCBluEmHwiDqga5/DuD2aCHqFLDmiQ//dDwf04pssaHYIOrrIlhlfMzhTm5OR0UQF28IRccNJl5nET4fcodmh/vX5mUx2HFwHCMkHEpW7uoHpjlZ0ZQzpbGhp7rIU9uSsQq2LlIF+XaCYsflLinSjuTbGSNyLtMvoyZuAbRmRQrpMZ0PSs3UWXUqzrOYqol6jJI5P11+N7aXdT01C99+IimsaEzfgHxolZwB4/rGWe4979CKSgR4bc1O4olwJ49vYrsXgRzqQbLfI+jEAUAz8993rDzYfy7M623RpW43L9U7Th2eYdVXa+eyJOYhckcJPQNkTOTs6GbPx1s3iGOIuUtHWP2l1s3b63/l0DfzMSiNj6l1i69AZKF9A4AmYA6lsGNUOZXxlg3sFnDRqho8AF7ch8JF7waUBVznQ4U4lyNVUoJO98Nx0UFLcEKDnsdSBGclubBjnQkwoBIPcGfreNjYTP821cimVXOFcuyDSPBTWIAq4KQuuXUPxLhBa6hv+zHTsByjbQRWDEe1UTgNpZ4LFJdwO1BQ4Nx6IYaKhfKISROlTycmsuxGiNDtsptpQXzolre1jvJB8s7F3LVvvMdPRsrbQkqdq94vP/TFrFknq2jm4PvUS3YNF0JXwCOpUWGqhe0uBnqXgnCDaSjjyQNFOrNoYcNOALI/2cQk0dbHDpM6Vy7FqwN1dgHld3gOIRjWf6QsFrB2cJ/gYKct47UvBwBx/HPd7QtdOaXT7HQz36zi04gJ0iEWSZFCVTb5dg4Sp/hp2OADw6c8/ydToOhNzVhB3lUE09c9xOdwXB5WkiMgze3X4pJAQrNfjICxJsnS5ht3iShU1JdtfXOl9a/WheTnYpNAZS9hLIuvbj3sHh2uDPfxJqHYyR/NeO/CSiC0p7ariLkW6WolDX9uuH+E6PlnN/tgnMvtBsHDNfHj2JF2EFqcunxQVaN3WFSbCVX+rRdkpT1TLF8/8lDgYcN18oKS13mxI2t8rdK+ed7XEcVsrDD5bk7J+pugrp1lbIKZWNc064vNjGqKrlAp2CkAbXyPT3uSyzHmAGBiqOGz6tgz7qwjhlnI8yacAosUjTOe4WenBuBbsvHKPfokCEpfC0lQDfLqAlSq1A+YGELgJsUpiONCB778/wcX2z92OVCLva70H7M+OiEahKTyqaw75G8lNhDU1fYdttsf2w+CX6THW/G4PmJHb6J9Wo1OiJ+0h+fxWqX2m/fuNItkruwAN0RD6GLGlSONJS8XDQha1nsGy0Tu2A9hdXNxLLD2X3KXsCU01Ej8ng3iLBuVgYeO/CGyRT78Ld+CB6p0gyuVbmOKB7NMF+Ljk4A/zMHmJAzMhLL+VgGSJqhtdrDiM3g9/JjSWGL4cQHYyjcVli1a2+zCQSU9TtC9lYLT0lkxwo/DmE0EKgdsslW/UYOxw7Syl89S3uX3HPDbi28BWkTCHP28T4Uhenj0fC1XfLOy7qe0HtgjXmEo1iMlGVd4NbENntAL661FJdNPCvv/x8/Jdgsk7Jur9/aNLTc4kqvdxX0aJWOyxBY9zM7+SUp2u0VsSqsqW9OA6NtrEB7BuI6B4rfWfccLqNlxHphx1c+ZEqLONcPEbsVHYyOy5KCejdc/8VVE2AoQX8BLpF1AdyHxOpbXYcL4FhRLffhLxRXGH4/3ld8aAGsvzf766YaHTkBVQzrY8ii3T9jBP2q5U/UgysCAP5F9JD/EpwdfRLmoIoHl/vOs/0sRklhyd/0hV0WrlQWscNQ8CvwKGxGJqwpi8YovQMP5pECL0RB+5+PwXOwxiT92UFSLW7Zj8prpLFxOY3o9BEertAV1/T/UM0glwrfbPs+iN++LVdEniTnpMcRGKXeP1Rcx/y+THTdZIK3DYU0MwyvlmSL9dAMBMhO1RE6ZDDhQ3qqIekQXbdl5yiLlVQzc4bdzyuoETZJnj+ZsNYlIGzUSlFuCjUjL5pM2fxOJ9mN0uKQ+zHE6Ji0MjTmcJIdmkuTcbIo9dwrSyING2UtgDrZCG1qC/iJUzf8/C6IfXvBtjBGWUtUmx2WRQRLJ75d1z6Or2oeFcmTMbyiBQ+qnQHlObsBcmB6k0tvHdX0izMZHMPILKyiz38280EiQYpbfQlT6RrWymYxj8rWyDMdfrMBohzaNdG1ChAPj+J53I89yRPgpXq+IWTIHxbNs6aeBmYPDbY9bKVGlWD6cAeVU3S23RE9mIKWUX0csZbOwAI1ntHLjpAX6v93ylmIMorvG0Oicxo4v03vNfFrNnEOC6WbUHcCMsvCSBKK6BXi7TKtcZ832qfKDRxHOAwmquowQde/HA99hRM5OeSqY13Di0VAmpSFNT1QqsbXVtXWrjqo9amr/KB9efH3IdvRd5VQF2n1upJgvGdwSUpGS2huDXV8SoTKr6P5ocDYHrKx+OE60AFLQ/j6QgyVQTq/wAAMD/WzKeBq9bDt11tc78C6+EWCjFxRnRSP5ALEBnAhJReYrJw3VbrFB0c4eHs0Mb6DxdupizOx39oo3XfK1cZnZiBD/8ry0CI7NKwGRQhVEfICaINZbCWyjY2n+WAHkYggnMZkISG52FoOCDjcZt50zA9KFqHcL2BGLjdErPxfdlO7CHGXjqFuDdwWLYndNkaEsbYeG0H+3/BND5Zea8reVijB9LEq4AmMhLlofCli9H8Ee3XDJotwZAOCudhja3bGvS4roUe75kVqUmAipiVCRQIcQAh6gKA/WDQkDAkM0EN3/G94Uihew8gfpQpeqAS+DHc2/qVyD6qFjcLEIJ/TniUFDaFHKUaEqyIqQ1ne/GXgR1YZ1qlExRYzfVChxkr/sGVUaDb80ZLIJd464LRTHbbf3AmVmqex+LK5c6G627AQleNZxL90HurrXp8JzTMfqZsid/h1Le1h+yzSqcNgyixKkEyRM4/2v2+V9ne5JGBCMAmKrLShqK4gWLkU3CQs5lx794BLUBQPpwUl+zaMID6kr7zcqo/hn1en74QStyBsSQo3MHhLSzbHoflj6yqCaWEF7BhKrnd+pg9JpPfSUWsM2g5Ew7knfGOluXidhQXBtysRGCrK/mEIKt9/OufDOnEACzfZR40CipgctQH/Pqf2BVlFT6ziQXi7jKw2YFuAAbRyi5d24bmbncE2XskglwhoP+m4NRsc2K0785k7ElivduGT5EexKU241oLOqAGOa96avWhwJr3q/pzQbgeVyogG8invvjaFbEu/nMrzL7vZWCfmplNGAgsCmGQYq6KFGWD8VSlwQYgAbqDwXA4/0eY3xwfaVBptDQ8vM9oVQ5EuI1UcACykVcSrXb+v0BfgXVU7oFX88qSgCcHfl696hWJLB/ZJvF7o+4HvI5FpPGm50yn0vei09d5w+GrSJIlro66B1eiIrCWygMrMy/HoziswYOM8h++AoR3a4WAEYrIUOKtWOTbcey3bZzaG2WcSHYODwtW4/GAwAAsCaQAQQZHTQso2YHAAotIIRFl3u447tvCdo3U1BWawg7EyDzGcHTzPeHs1hguK8Bxx1DhDcSxuBjuSL4S4dR8TA07pnqB2YfPSDTUvbfJJcFHjmZNAEGUMgeFAp8Lgk8RDRYbxdMZLNeTy/iC+LsIY/l/JZSkbjNxUm1hKxSvh9vUqQDF5mkWtBt9LLzx1M2e8B+BH9Oi1+UZ/FE3naLkSSBk9Qm+gDQdjG7YGiPf0Ab9PWZhNknLR9dUxpIvmLr7url9irCXyS+iSodWLipmGMMKD8JrfgzRAZCLOVq2kRQQYoIIjQVHZRKJEQ1AEATGPIPT/pnt9x1kz9+tfWPrp3N0SRO+H8THtGtssqx/tjiaOS29Nr5wzptqm+BjKiAcj3tgagyJpN7N2KB/yAnFYY3J5j0IWSXrb7VYiGRnqHss7IAeguk/TTeNXljSzze4d0eUu+FgqA37bJCdDntCGe1sJrZVSBkt8l4Xyz+KW+eoiqv8TPavGLuj1hnb3qvV8lJ5OqE3v8OZKxcyzIONYXhrRSUuSJyXSlsng7XWigPiswU4hx06acAKqKCNWYUB5AHoAHMc1+mZRUYOypxgYKC9NOCcwNGuVg4VcP6EcgIULJIbIOQespTcimYG7QSHYC10IpVjIxvy1qbX8lPX7aol4d0XdiR3KdSEsCZ29dbPuPSVFSv6/h4VaqZUcQlDwk0LZePHJ/lq8z1ss8INpjQ//6vkeWxgEZlc8YGBBTuB+fGlEAAABwdux3dxL3jIC5zLzek2m0ltWHOKM6jCPdmg0tAV5zcC6DzXHfwH0XIdtgI/7hOGXSBnsXuGTSnjICvKvyt/PKS49LcMHBut5K9BABHWwBmm630qRfY1WpN6MVAFKmo1sp7tJ9Yr/rVNE9l5yrNS2dh8uvqe5rT3V6ujhhusNL3uGRAacLI9vepLKKU/OCcxBCHF2zLVrpJYKStAw6J/k6jOL5RY15NdSS/WXyC6mEESoNKKkdAjBkQADFFAuYBAEcb4hkTZQAnIl7fBBy11w2DooAgB8IrJTnf/yCIXLYYU3cTe2loKrra3w3dqigUqidZKEgW2uYc+lxMoB6qx04IvLHGNfaOVFb72u9zmZi2fFBest56FhKl2rX5q7rC6+RRezjW19xVoOoarixAlsuIXW+KoFhmLR3/OWm1GKZLVH3QhBDVP/r9gYSAOSCg86y9EGM09SwyAAsAAPz8kO7/l0z/1e/Y7C6P2TckHjPJ2hquqEEIAFMHsLsBie74m/bKLuGLhnJ0TxqGy+DRUZh7LxksnzbZmBjmgpZUfGMPeZZnuFSqvDOCT8aVBZk+qMOsC+6TIzbxCJUQCtzZyw8XkpPuzglJxm5nrGNce8OXmVNQ6t+DsPXsA8n6Cc8N7q+02PUXP2HUterGtegEI9Yz+9P+1nPozxwCfqz0DAkxZAEoxhpo82xqNLyvZI3oiapmu8DMQfEjcgX4v8ALbrnBUoPmCk8d5DZM6TgwrBCkQohY0ZQZwjoQBCoAWmwksiJzORjmbMpYxXbidoUaogWg0H8kkPhZFZAPVZLDDsTtkAgpDb4i51z0LgmYE0W1sIq8/IoNJXvNsOLL0lWBRKzARSeOs3CGpSRzJbqTERE0pHj3BaJIZtQuP+aW2b5glyzhJQlMj+pt2q4WC6e8k1qA7gJs9zP3aA6cJbVzSLFFA1HvhTv3kIB+/0VTCdSoSDyIP3bN3+18CJB8fgJ8m8hvLBn87wthzniva9rSIhukgA0+2dkkYmA1JlagaHvl4PTQc3+GnHwkztfhBXC+6JE+RQS4Mo4JbCuHxlKe+Z4/aGeOLSjkteMuvD5hucqkVWCkRoLKJc4ZqXGBlqP9HThInWHlhzPrI1xx4hh25S89i/G8G44WSEUa7O/nEKX6Ym1Ld11RHU9wtkUEMZNXJo8xV8VHeztXYs4HdssjbgddSkAUhnmRISSI8+6U/IBVACxIKNrBldZGhWHpbqnIK4qijteSUSIzTMXlt5rRw0KoXaxWe33BS+nU4UCugkbZAEtY4PuKmgGMhGw4IU1pc/5F9gK+xdK6Idrk/Zdn6f3ZqJoC0odJyhF2HHLggAOpfrFZXOsC8w/m2ajchB6OGVUNlaUjDnPTBP19jTIQEmxwIJM1Rdn1QwAAIKICGSCIQvp3i5KwwQqKcnbLIASY5C19tM06nmZ8+9O7zXNCrybsHRezWWEAeDQ+XA28EfuywsCG13/sFeVAFBa5FjoJfH2JZm+Fv/8E71RRg8v4TcVjMkTI8f3FjJMT2Zrkfz00hTkRUHVxBMGorxVzQPdq9BJM/9j8i7DFGFm4nRY7rebWkcb9ma8A7d9rQZYPrxye2R0sBnowkKSOoCyd8G4VpXR5ihIFKy2yG7CNMkJpIgA0465VlP0vF8kaOsh6p9qyCwVfhZcMEawrRoxKR08E0Auq21h0PDN3I4nINAmlw/PNK44r2dwdz+9NUhrLu6Rkpdt3uHSduQFY8qZt6t4LuZ5jsO+d2z+E8cB9+1FcI+Qs4IDs33EJIrH37YEyEau7RvrqderdmUVgHktyfdHo+mByP6FvvINAH4l3Rl1SNp4FF5Oeiyk2mpV047VhdwjAX8dXfNRh635QFqC0uonlm4GRQeLACvN0I8WDxToHIRtT7aYdrvi+8N2q2i1DtoDSlUj2pJebKAR3cYDIWZQOQJ8esTZhMZ69AyUpFdi/m51MOVY8p4atOOKANL7ayQ8Bsp2mnZWkb85zrnWap2KWq4FIgDuynFXtRQx9AAC43xkLtjBcu5KsIf9wsBZumKWpCaKaueBcCranRWqDyOn5KRE92n3LK8DM26iHT/p8P3bO9HSQghYK0o+1s/YbpARxcaT8geLVEDM4TCAjQUjyAQYyhwsT9XxF9kfdeH5n8Gf7whXb4pSrBcBJGNyuvdVnGqpe4NUdATBW20hrckDAnUHRanBbQDCWeMwXR3DIeovtrCCAYOWAxPm/rLKbGqUV7Gq1VPU3KM6ngaR+ICBHgWlBtZJylfv7CnvmbZLdzidFZ8wsAleeMmItH93OSBrnqlmJbr8pFWOYQ8NPAAAsDJu9mSnMuyZoztsvbahIdpoWDsTjP189meNuc4VfxnrcHNNA90aDvhgobzoHjaJyz2JYD8HigTguwCvQZ11iLimenQiFzf4r2zRHPbd5NOORKVGEa2uvN0KvHHFNevfK2eeiYKX1XGWoT5r8/gF67zIqci0VHNsdxFD6+HXF26EmMb1EJYl77C6Z7+lRCck4WkMv+aZq5JaFEIFg3I3ZuAN+hyHcjvVKMn1UJ4veAeFM2Ln8DI/joZzNwhsj1nj2XtpNrKuplcAW16BnB8LlulMJfFv/etfsrOy+4+K3idPL6FVkAvBQhyuzK1V4xr0tS0VH38TpdAVF2PP8b3BiSr/FGDZk/eoVhucMC0TD5PSoHmKMrRB3pMGkJVd8juS9Y1XtywgzEYz2aMBnTfe2zYjRkFcRYy9G26Jl+Z1jsgC33kQ/txIi18KgLJdEw0HPqzx6y2IaohmyVobxqmDMj2KweaWzBug+C6AD5ssTzx3+wJFMwxqxkRHn1GNIG1qlf5Z4a/dgJHhnBbg35FIjllT51Kj9N5grEAYl
*/