#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_spin.hpp - spinlock pool atomic emulation
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/spinlock_pool.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using spinlock-based sp_counted_base")

#endif

namespace boost
{

namespace detail
{

inline int atomic_exchange_and_add( int * pw, int dv )
{
    spinlock_pool<1>::scoped_lock lock( pw );

    int r = *pw;
    *pw += dv;
    return r;
}

inline void atomic_increment( int * pw )
{
    spinlock_pool<1>::scoped_lock lock( pw );
    ++*pw;
}

inline int atomic_conditional_increment( int * pw )
{
    spinlock_pool<1>::scoped_lock lock( pw );

    int rv = *pw;
    if( rv != 0 ) ++*pw;
    return rv;
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int use_count_;        // #shared
    int weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_local_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_untyped_deleter() = 0;

    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_exchange_and_add( &use_count_, -1 ) == 1 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( atomic_exchange_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        spinlock_pool<1>::scoped_lock lock( &use_count_ );
        return use_count_;
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED

/* sp_counted_base_spin.hpp
PBNm1tViA6XWkYiwro5BHc+pXn3hBY4bgPV3Nhh1L2DDuuuwFVk83Ap9Uf0xqgU90NhDzfkdPjXnt+ZjO7H50Dubry7E3YNMPHpG1J2zM7HPfA8BkDdfnStCqAxZDWodcq4Ig8XFeWWlbDWeaQfBo/oKbg6UjzaumLCiX4Y9nd1BNgClnj7ueHzTevbYZpiZ97rTE9yNDZ3c63Z3Cqo43aGSNVl9mmzB1GxPnzVZkiZbH8rdnIFPOSZdLRSh4lBJKrdjuSSEvXyabJtAZmHmZiaQvOg4Ap9x1NSvdVzt2wA805WYConzyt11sYoVQl4JEZvySk9xa+QbXtQvKE5lh3rJ4Jzle3+57wE6CbfRK6Xvxrx9904FypW3BZ9ZG0SPBxFyLIiQ+Jzy1bJAw+mlQuGPhk6wtYCtybCP6etsEzBHNAcM++g+eIbfWya8eJJ/p7lQki+5FahXM+6b4nY36geeNpZ86venVoUi/igi9x4UI2hsQ+2F5CN6bYesppo0hJh9cg34LpGwDxFTyj5ATJALiRnCLiVmKFuCpp7NJ04Fu4CYYexsYk5gU4k5iU0gppKNJqaWNRBzBKskpoGdQEwLq1iD7R/tXRLNDiZecWw/YiawAcSczl57AM1U9g9iprE/E3M2+w9izmW/JuYC9gti5rKfETOf/ZiYReyHxCxl3yEmzb5GzGXsC8SsYP/+AIfCziocqA+h706c22wNsZIJsJxYcfSzxcS6Hq05xEoekphNrHiXkk0iVrwazE4l1k1ojSBW3HJiJxHrVrTeSsqeNI871AByXpo70N1vRAYwHAJaZg44l86pQr60GmW/eDEfFiPGwHY+8DQJXCLZTMJKJRCmu0DC0tl6DOvKXlaDWkfd8VJfPlLMp5PP5zGuELkvUI6BV/nApVxgiC8wBAOpDC7wbi4w1BcYioFiPtDKBY7wBY7AQAkfqOACFb5ABQZK+UARV7EwvmJhWDF5Blexn2pJxXz7NxnuijCJp9h3+oScJMngD6wM8h1YsfoOrED4Pz2fMrbmDD2MO5/Sv/t8ynKvp1/d8useSd3yax5R3XI8kCLlyxi5dgCWcZTOW3MLTGi+oLOeABc4xaQst4AvzT2gq7zvIIW2poMef3EvKW0gmqS4ZtctqMt2fmMeZ2maJqS6HPMb1/Cmr/6ISgZyFKjmAQjPSXwC6GITYgEtI2f6NrQJZbVkvR6/NhCozpogfFayTUBPhPpO4WIy/yAPKzDZzh9E0Gpd0SBGhNMjYH5GeRSoTyP3ciM9xJcJd4uYf8/xLJcJzQVCso458zhkSVtgmc9yDRLoa5AhINRxDXIaGmQSNMgovkGkXIMw+1y3eEKrYamiKLD1BxtFbGLNUZKrph7zRS3xQVwZTAdUQla7FKaaD2v//Wp3WpgUxwhIIylA6gG9DPcl52VxmeriSed3Ilo68YivckyHez951BcNORifOL8XQQ3pwN9fheTBXLyzGI/UEr/6c/T/v/D+6OkNN39/tP1J8tbluQ3c+6OlaFLwZxJA6oa/+P4oZv6v3x/FWH/+/iifxzEw6gF2AWwH2AqwCWADJsY6/Le8P0paw4uVvgBAPSWQhzz1v+P90WVPd70/OuHpP31/tOIp0icYef06sG8HaHnqX7w/uozL7y+8P0ry/bfeH+XzngSGFsACEAcwHSANYC5AydOC/6b3R7k2WoNIAmwC2PG0X9/8r7w/epDo+8YPMXeS5zsz3L8hEev7JXQTbXiZbIwMWNvfJGNmc/yTkxUABe6/9hbDEca2NlmwNkMANjMOaxjcrJD5Yf48VJvSSubtxN9fose7k6+6M65CLLnhD0ba0CZvOCsHl9DwB3myfXj9fGeLd14j4LDPPcQtM3zC/ISljDD8wnyDlkHV3yGBqv4e/5qPMAfAc373evTXvie4veRDgtT3IeF8XbyX+5JQGJafMB7YO3YH7l4DR2zU0TnAvqlxZ/4m2/IY2GtbHr3Itjxa8NnxnsdLMW3bmyhxdgppsbmJsbuYwy7muJEZ0XVmd0SP3Xr8/p/ZHzhMoy2Uxo/ftIjs4ft28dPJxjk5JNziymoxf0NO9Sbj5zjmateu/ZjKrhPMp+3pqWzZZe7sBG7aj/Bt2uuqkKs9TQ4qQOXdWS2aDiNzmhlkzyBbcnh657S5iX7WVXk4Pd3uZU73RgH3e3HpcFVerYsbLuQLf6Gi1/HprhIbV2KJrb1KbGUGY+pUtmkF/92wiS5xVfZsJHelXOR121rrtEF51f1RvU8ySDupHFYS/FRL9vFdtoN51SsghA7Nq470epkB+JEPOoVNIVyg1CPmXjo9TnHnq8XQUpmIxWF0n2YvVJAvDgfrHPVs37dRKQG5aFRK9IxH75XgkbE1OGjefgtEsGU5KIIxEZyacwEd5vfMBDnmtmB81zG35/nIwbv++DvvIt99uaFyGOrtCSNHmsihJr7JqivP3IJSvQRkefKqCF5Fv+plS6H0Rnby36FO9ZJGNoxYpI3p7DCw4R0LV4JU02GW/qFEVm5UvPP65LLzzkuDysKcl8KWjmZ/34hqZSWozW9eI/sPcLmlf2ghritBMq+x+tJuCCgbUn0JWdml/dl9XHQJF30n5xpCXChuoqjZES+NzpDV7kNmKJ68yXILrOVdG+03UWBQJat5giKSqDdZvCzY3V+2UxDj6u8BxlM5lP+i0yevn9fbhuIBd+d7DZ6mrueufGtuSHYplE82ULbHdhXG/fPogVl4ppEHL+ZnkA1CW3AquxyP6MCUgNj92LdgxDRTdyDn9mCe2xbsGeqMF19fJnX3z3MDXyvksr8GNc7sOp8i5U6CurMkRNUUORFKl/GKJQSMpKZ+ee5WIbNA4zWukKAiiE/wKRN3stT5XTTHJXa10+GGywHukMf922mVXzvRc+psF+zAqhNCAvMSaATVhTFWj3+LqPK813ug0Z0sEe039i+XGleIme/M8aErT7v61yV4zZ9X9PP2T1yb1u8Pd+SaW5b/LogXezTueImzXmgMLO+H0d9yrggVlm1zBToDr5s/dwfSqISKDoYYrkDP46jMKl4sREUYqAADlV/kuRs91dznT/bDzT6x3J0kTYfhd4h8kZsOK46xNIQZAC0rz7N6qaWT1uBjxx5N3SzpzHRv6QQXI51RKMAPdul4kJbQFiACePKX7s8OvuarKiqqyGpk9U/33BgQP+vFjQH+GyxM6O77aSH8cV08k082eK/g+71Z7bIaJJnuWSHmY4SA4pMR7iSJMTOE0ZiPyVZPwtAkeV610UvJHkClPmsFa8SRMBpiYoiOp74CvFr2W9nXbaio1GlF9XUCJtV8bMlYqKX7N2y2gOjoZKbD/Dstxy3gvhNt8iOd0S5biPsw6sO3z8yYiUdqvPf6atxIJxiz2plYw1yDl7mrDW+78BG53eNCry8+t9McjLEHw3LmGYW2vr6V6T76Hrb1il+j8cNj3q84PEiWnL49PGsEnYNfYyFfaPkvzY0u2zm6AbPbXSdVmpNCloZpjpobVwxeO33wBdOnbpt0jTSQlk+NN886V+Fx2uRCMxNS9qq7yfM0dvPsEHyiWc7m7Yah4HmgLql9ht1u5xHv6tpGWc0c6CUoRVY7EywJbXd78cWADT37ddLfSb9KfZDKTiAnmeXcQXToUzmeW6EHG7NCaPnaIFMjMwAQhHYUwUgl+/xZ+IyQcV4IMwiGpPlTOigPyEceeWvb0+pOTugiJhZ3/ARnp2DFGKMtpGKk5oAxSyp7vIH7gFzYx7tE7PtazfRz20LM8RPKJhjmC+ixkMzzJN6awkO0eF2mUNAr/mNs2mW/vmjDxzzZ8id7VjVmY++qDvVyVSW7CunsisHc3Ie2DSDZ9eHnA1GiGkLeGg+FlWad71sjsh84HPCaGixFkOO3eBQL935Hug85fxztp16mCUlOXLW4SnENd/9x134DrnGfv0rOeZlH4hfG8mW4DRhQZ6ntVkmjrW/4UegO6ohTigX0bDs7dDDFPTnj8+s63KXjZiWsbJ5b2NhLvhqwMWB1KoAjOMMdSsYlBh+CvBXKtbMFmF8jO6g7/gA+/n4vW/Qqfhyo2xa24CruTivE/O40fnT6cDtIEq7ajfi3co2rsobMchfO6tqtIjw8+Hc0oA4NVwLSoR51I/5OqiWCCiHqCnpgoTAjw/sORmNF2Pr7IFTUxC1c+KooV4i7dhsWYlvnqnxMtvp3QkfWTaxDzzrbBlflenMdRisf7561zmtbt3ZgTNXlYCbYa6tpovpFe23r18jxb3XlegoqUHEEd643TOwsJDvgsFxtSHWLvFolt2EMHTnabasS2NaYmytGuW3rJpLSNV5zLRZSVuPhiYDL9pgG2CWIJqvF7V5j5WP03YUB84zMY8w0tvFiV3s2gNWl9ORn1CVVzfC+g7l438E8vd1F9oUioXYu2xrPtq7sPZu9MLTdF3Ge3+EWYZtF0zKuNaoMwwjlH8ZmkpJGYEkZWJIBx59ooq1m3hx3HfbOfHb/Wei9jzeJyDN60vytOPDSX/43B96mgX828PDMc9fA+6Sjq+L7O/7ZwGsfSAbe093xN/DxYeD9vhX5woCKHLy7KYewfjQ5yYB7Ha4YCd3PmSiVNMeEYphnADjEdTEhEABeKCu4YyTObDHlEpBdDDM5/FCG1xNQePKbljApZXtgVjpboxs3KxjyMGxhyDwmiOi+8ASamyqD3E3PY0ihOJWd8TV3OeL5UAc+mFMoTnfpMIw19AgIKBw2e16j5uh7G2aTT5jo6ZIKnQ0K515x9aXQOUJ5xVnNgfe3QrD7vLsBUboe4Na+w6PkFq9GpgV1YoicwV7nXkVM9WVJJqQ6Ql4FSg+B/rfiDXaKDmhLGoiKo6GapDhzQ9kt1s67hfKl8okN0KXOenkqO2QjfrVw1itSuXdcSHRnZ0hlXxJ8Ec8jop+kV5Q/z1H2t+4cxTfm2P50zxxJFJQn08EvpG89MwEfwULhWHP04nn+4avz7nZ348XcMLy+14Sm6IhnGtjxayxuc0GcI21HTh05e6Sl7wHmwsXf3e34WBbEiAuTX/xRdKSsvxniLZWUycwQd0mf5IkQMDwtLERzCmwSsEkvfnWxxfkV5f7Efcx9EsuZt1dOpeNyoOnAv/HewSw3I4WaDght7Bmm/L53mETTAf5neqTx410LA4EZQh4gXyzH/T9Jk+0y5R2cy61b5IN6MAazZ4pQKEq6yo74CTkIvNGMs3T7C35Kub2uyoOuyt2wOLpDXVn1rsp9wA+YbVJZTTl+zks6PCPVrcOnR70nABmFs/KwgBlWZztMrpiiVz/iFcTfADVW7qOHoSI0sft3D75NzH7ThEi0x7uY/XiocT/EYIZlZNj5a8KS7nvK+80X6dkok3bdTx5YzImkp11Zu/DmcYadne/pFolv8QmoY+4lChFOkZNskM+3zKj0QiHbgaetMt0t4MZlBN9ha7btRjRRLK7viQFyh05Sg1BaASsId/EYH0eW+qRmGjjhUBBVPfOwEkMy4OcfAZi7i3RseqGArSQFQ0xzM62GSKn+0czNeGL3IBtTjGJz5UGP3FlZ76WD3UkhLgHqtt9lrNxNB9lZBUYgMu02VLiX8Q9gQKZsARrmv1nL7afg9zRybnW71+0NrqfVZIN67Xj8fraP/mVSjGXYsANV3ymEDeKY1a09nIZW+tCw+hFe2Z568vEMp0ShIvOpi5cKR2dO/MT5iffY9+SG69HakGq6D9A7p6WaYi5GOztFFRdID0CK9AwujbsCJlV7nfjdVJKaaOKd6VWyFHdELnnZiDrLuyhiZ0DTR7BtMs7b+au4tqPyJ/5RRFwQON4/pVBRN03AITNv4m+QnfsQoNOC51ZCNtC31qUIZqSy+FIsOe3fnzxlDaOetD6eswb0MUWhKPPWkA2x5pOVfeosGyZ+qqn//VV87Jmcb+eezxMXiu6euD/drXRpBc568Z3MH0Bu68nrU1jfYFLf9u5rrPjSik1qx4rPe8p9CKqeJXF+7sVThJ8c+8ll69TU3z5LevFLxEPrdB8a+zm+3PDJsV+Ao+3LXHWBH3Ph2I+YrYu5WnGqUDjbvX9iUmed1G22dVYEuQe4QpwesTPMSSU424BuV7Ldr2CEQtVk7yYE86+8XKr+DrV/uZIk7oRALCZBKHuXamiVV/+Eb7FX/+qNgr9eAeoJJqTDldSZyozSnGKHcU0nq/0QpZbKC6+++iogQnR44bPD7LfX8UOghJCTbI6Lh94TTMPvbfsnJkvMlyqD8bF6TOixmDtXWiY2IyvEkgsR5A1YsGSksp/4ZRSK53vipdFcnO0kW4XmlKfWHOldIq241ZdhVdLFKhKlDhPMCxGNytTUZ0Z7hoC9ynFxJYaJvmVLyJkHTT2OuGSpe4n82A8gE148OfwA7kNSVX1P9s264LweDSJAktQ9q9OVKXYN8AQ7ryuYAPBxDeVeWFDAEurj49knuLuXjfkGf98q3tdPRnXhC5y4j0mufp5LJU+mfdKf0GVi3+L1chc/w9jHv0My/K8S1/klruxOPNuX2D1L7r5TikcFak+Re+t1KwRNgUp384rRriyJ5hQ+9UwHyvYcjfGICpV3I5+aJGHaIFntqSZgVQdWGXUV/TyiJkqZUGUw0hevU1WRKibAO1XsGZjBhjfg1eqMdPaLctLdvlu6M9yzpKifaGogjPmPvEEURV68wO3L/Q1t4nE4AGGM26TuqWL3QNm7J8d5vTKq9hQ9yPwtLal7j7IA8zPhIxyPnltB/mtkBoIQj/duXLPFrtA812yJJ6nuPYGFKClwf9LQNrihtW/f/X3xPq+k4fu+tYfwmSQ5M9otcaeK3SePfN/gGd33mOhAdTN++qo94UoVuyT0dzi/Ps9zJUi6p0v3/WKiYJM07e2ESuAN30KqcADM5jqm3X31hRfyXmCjBlDk6nUl3tiS7bGdcAXKPrIdd8WL62wtqRnsq9/zvaJwrZC6m9gPv0W1SbDACtkhTi+5NIDKpESF8tkdjWJa5Nwv6WiUoCnuaJSjKexoVKApQE1TAf0oSkLNkr17LN39yR58em/soYyPKOCsP0SOkb61+hLKGHQImMDu0hLzIaZf32ZPn74feyAtrGdjv6T7mr9gpP3w6i/6QbqOZui6LJK5mCIYyWlBdDcePryEaMoJvs79iouNiAtB0f3p+4jD2E/S9xA0xnK3Uugh5kNQ2ifMoH6IqgcKBaSwUMDR/SlOORG+P3AJcWEC+zZ5hH33YrZiah5ig++XkrMufztZedWddZX9HCc3UHTpxcNjkbCPtUn7trB3eZFWSU8ulrobeSINA+qiF8/XScg9fjzqFswOPuX1Fg5hE5DxzywUsdd2er3cjRs5Of9alUPOvy7OnzABd3jPkEPjqHXkUWTpuceER0wgjwnX1j+PsemKfCnnkd85Ht8QrgFPfEOYPIn5/Br81DAq//R4X5r1mKZf/j7O4/l14NyMf8htxMPwd2Rd0tUZhVLcVCkUAOO6ngsM7LB1Cpih3Aub4rLgqqSBCs/tIH7pwCb2jN5cw8Ub4j2Mj/TQ/Tev4TwC7OjjfxQe0e4e7XIy2iFikDX5x+gPmOR0vBPoHXwceRTmqobp9A5uwY3xdu5tYjRPEzdODO/gVoxn
*/