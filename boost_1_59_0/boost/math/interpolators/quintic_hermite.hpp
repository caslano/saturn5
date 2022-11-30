/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_INTERPOLATORS_QUINTIC_HERMITE_HPP
#define BOOST_MATH_INTERPOLATORS_QUINTIC_HERMITE_HPP
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <boost/math/interpolators/detail/quintic_hermite_detail.hpp>

namespace boost {
namespace math {
namespace interpolators {

template<class RandomAccessContainer>
class quintic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;
    quintic_hermite(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2)
     : impl_(std::make_shared<detail::quintic_hermite_detail<RandomAccessContainer>>(std::move(x), std::move(y), std::move(dydx), std::move(d2ydx2)))
    {}

    Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const quintic_hermite & m)
    {
        os << *m.impl_;
        return os;
    }

    void push_back(Real x, Real y, Real dydx, Real d2ydx2)
    {
        impl_->push_back(x, y, dydx, d2ydx2);
    }

    int64_t bytes() const
    {
        return impl_->bytes() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }

private:
    std::shared_ptr<detail::quintic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_quintic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_quintic_hermite(RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_quintic_hermite_detail<RandomAccessContainer>>(std::move(y), std::move(dydx), std::move(d2ydx2), x0, dx))
    {}

    inline Real operator()(Real x) const {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const {
        return impl_->prime(x);
    }

    inline Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    int64_t bytes() const
    {
        return impl_->bytes() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }

private:
    std::shared_ptr<detail::cardinal_quintic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_quintic_hermite_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    cardinal_quintic_hermite_aos(RandomAccessContainer && data, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_quintic_hermite_detail_aos<RandomAccessContainer>>(std::move(data), x0, dx))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    inline Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    int64_t bytes() const
    {
        return impl_->bytes() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }
private:
    std::shared_ptr<detail::cardinal_quintic_hermite_detail_aos<RandomAccessContainer>> impl_;
};

}
}
}
#endif

/* quintic_hermite.hpp
1wJQ7vJC+xKcaXswQeBBNsrs4m1KeJXYYl8vJK8VZx1Tr9AmT4d4A1uhHuEnYg60r2wK8SqIFZNFQHrfLnSrtPreyc+UuPoTdlFdcV1ioT1qAmL70vvlOZD83nfIs3V0DaX15mPXDyX74TlDdQPjewST9wA07OMKp1B2P4u7ZcoNb94vFqK6y1zkjPBpKfDG6w/bjnK7j+fGXaT2d2GDcTrKRjW80ir8zikHpwKbJJuUf8k3ooxBZG56a62s6/dXShIH66hE/U1SZ6v0bEpZZswbHdE6rZ1MXpxItAGg6hnmSrboKzGAu/ECSEqI1Fck9maaEoJVu5dN52kkp6qHBkFlYrWeMX8/gqLDAGNZtIlfQEMj4TxE3Lt8KPVPcKImpUBduTMcJxXdmZ674shIIjmx6fbnyGw0ejzl5l2kUWzvLbR+HlkYqSqD6gcOSf5/eNEMcuoCFd/ODLGhBh/549X4XtKJyFMkByQYRd+67gd/LFXhpbuj/lfeqB2ebGEADdNx6l8N7lERNcA3AXNF3rvhfZfcKQeH9ImeppmnuS7k5Gw5DpLW+Wufb7X2f9vtmx9EzYIavcyr9/5o2G1BQlu1BC5E93Xl0qyEr41OX3nLB4kXOoQZ5yO15dZauaFu//+PGy5ibUHFzSLiB/HTwljwaF4Ich4QuuMkLdf8INSfChv9n65m1n1APUamCPq3HVcBmsMZN8MpI3K569pK3cC/m7vdnxd6p7by9Tm3atzkdesHO5kdWuKya3/898euo7f7obmUsr4bfLNN0qPE/7wvjfjsGxzIJMGG9e2CfyE9P33Pzp1g6YkHvjKg7Y4o3KnBQaEcGovQdYUsQA76OYx3wBH94jMH79xCMw4Yd85s1E3mQokz5AP93you9zef16nykp5Z2wJMx3kQqf0l1/kivS8Q+hbM75U+/RhzSx2CIMECH3mvfwVx6fdIvu+2YjMwwncz/aU4leB3k9pC/3e9/eyqNTJQzJ2P690mhw0lu9y+u6PL9+yczqoCl7xbmemmhlCEU0g9dCuRZq6xZaOpqqC+AqNkpDiDkxS1mdu/X04po+1XyODn8RYoQsPtfEaDadkln9Dt4gBMDS/ARYgsYaAK9fS9GkcUMVLB5aRaitHOWTLXK0AS98Idk8Ejt4V+7vCvc7l9uPHHlId5eYAOeRvbancw1jRVL0a7sX6ApCfn7PdMknm1tTyLSBPEk/uBBDZtSeSrzO0uGQ+5DgRitkRFW/nZA/x06bmw/IoPWtcBrlzfAQtroGtnruBTHWKECavn86Z1NY7dKRoD0K/h49IRDbDla7VmwnXTMNpyvk4L1YYg0xX9l175uNNm12DMYxfITnYRX4kNQ16+P5VYcvHFqrW4lXCrdsvpuZXUveXXa+NtsT4Zc9tbrBLEjNHCw5G9qu0Z0/XdNcthNgEdUtZXwXRgoUtK4zF2VBm4nTnpjsD4FRA8myiHclDUkJ5m45VymCxV4qbx+46l2nk9ET7DrpGryE0qNC1+TcFnLwQDQwwHRt6kkKnKehi919Cj0piMavlqMPNNfujgIL13HilHn22oezGoCg0EP6+3qdbNmO45N5KayfMVJ7fOpdX8SOfI53pnApa+CM+LwJWtT0iq48+1tye/ZmCtFTxuwmE60SKEmew94cT7p3g9eZaUj0TVdiNyO6NhfjIhKzVip/JPUEhUC9UH2PancmDpsWydptn2FfFput8k2Bvcqdz9xFO6nrIcWOiuSTMo/NeB6iVKVqSKHszVZdZqnT1pNV1ZJ7xhDjLJFwwUUDtA1ffk+hxz9W3DPu7xBqgt3gUlbU0q4XdqQG7HkfuebNR3LTzCfpIZo9GOEDkO2r5lVOaViKljcEuIFmTHe6VCoMt/g3E9SzX23xyyiEnCHnaVPb2QbNCVgCmVbma9jV8GjRM7qU/dQqI8FSdCvyvrTUwUIjdBLei7oj42gzcwTL7aKlM0plBi12ujli2l9UTWqR6Hwnw3GH7aFQ5zmooiqdvAkmmOxEtzNg8Pf+uyGS/JvruEb2YdSOGrOOtqdpq+S5XfPvNoKLWun/f+MbcmV4oX/WCa6ebJxfQWMTFQmQbTiwME3m6VUK87r2rLCBWgoEsK8haWTL8dCt51Sdlwa6QttPPNzTH884WAR+hvv+2IFXyd6OA+OjHSlM4piGkKOmuNjtg5wZF48VCDLYeOlJd0fsDoJN2sXxGTNZvZa0PBj2emdrqxDFU7L4Rt12HNsg2NOUrTispKe6rnwVTsKhnMIL3PaUJUFBw/yyPT+m+ABJSoLSneAKxVS95CcwMWYtSJ2vGdJ8eDK7+sZqV2ofFvV2rP13q6lX7xs5aWPsUWegkHutOpajUL6IFrj1WSYq3F6+zf3KRDxm9klQv0p/TqaM9r/Hfv1Ky4pcabzM2ao6bvKEA0ATRLrfRhWj3jqpdTSRTgChTOziQ2cuveg8YxbQQs01FwI8/DN2qLVFDIFuHcp2cZ2dW0OMj36kU77LWohFFPk8UMl7NSt6XPzLqNmMeSnqjGIOjPLUkIrGSW8q4pVohPtLpXADMTyyQDjmPezcEiw892OsbRxevkzpvPBZouSZpeUVVbFfWYT/VJt3dzB1IsFnyNMoas/QzGI7TnbIyaaPsTaaIpvmEkx8tgrqbSAAr+sQQ2Xr4Jdo4REtEm8SGugHRD1irFVY/Fo8DAo08Kn2G9xGre88umHE+UNufjU+GNfGMEJTwrbuvD9nBxkhJhZ23tHl5VbotRJpuwXioSpbu0N4iklg3sdeqhUfAaUzuF2C+7ZMwovqcOJB0PsNJkF8D+DOQZY3JqboTGFt9Ovx/G4+53osrnqewVBD2fx2BZrbDkF47Yp7xZIw0Qk25cNjqJybTMfIRk+r0Ii69+yVEdwnSOq4Cyg3/i2mKThyiJg416iaB6W2qP2EhMSvAZ8ADcYPgGfjPWkgfe/zIzOiI8FJIUx8S+zqW6ceUsSCZlctYb72LBN7rDNHQiOMkqHUJVedSeiTAIl/QTWK75LK6Lu6nab5JoDCsFZl8hmL24B+hvEMQ0uYo2klxv8Xvfl6Wp+JNUsbhNidzLSey4UrqdAKVaAh9gTGvR1XuN0bXLqhcyHTHbxTxNVjrxUE9XjO/Y52mTUDF5SdH/yJv0z7Dp3YEKO7apnL/Ncgchm8KemDboivGk3UZZixODeFSZl2sRMUHwETxZR56yicWXz3DbO0gGFMB9jUbzPGtLL54vfziqTDXQrHFBBt+y4cHUGYzYpr/wxGTU5kEMFfMdezs6WHqbOKkYs33uOMhs9U6bAu9vuCWYq9/VSLXXKyVmvlHQh9oK7LH7VRGk/OUBxMwXDlr8+3XWwI/y8iguj7R3A64dbTASPEhLXDOxhGx69CveA6+XiHAUw1a0qm3musOGxUFVjyN7YeTgiijhRG8M4uKVdNh49jntiKbovZGHu1MZkHtA9x7W1qbVb2y6lUOQvBBtq34hI25TmccvaMVy2LYXbNIHzDLC5dy3B7HtVp8o5yIcd7HYgzpTBrd7Y8RSyDY9qKPD+FWDGdg+pyYGrGurUkJcCnQVjPUzWXVLAxWHOfKfcn9whvVtipHCc2PAeoTSR4Fdj8OOk2leD9GJtguxrIBDnlbxRONzIVyI38DXyAnLLUyT5L1nGiSDxZHR7FEBO5hhLT6llSRg0aasiy+7Q4/Q3hS867sSCtUsY/juCt8YrQfWluBmrSX2Pq9lJK9yXzQcL0bx7TjEwFl04CEutjXsmkx4Z2A548yIaNylmiwVdKLl+uG6NjfTEY7ZfOfp/48HqRTNKLdmuwGfuOSOeGlEzM8TZnnweDQbOxSYyMs78NRbrzIfYY4NRpMyN9XaGM2IRHuTP3m8qftki7srjrJpUOZD171Pvmpes7bd1O1G35td9mowU33MXhMoiWaZXglZS6Gnh9diNNWie5i0KZMcgM6g0yYOvwtfK4dWxlRQ6nUMLdVDDRuZE5JEBkeqemETUN2tnmV5j8dMQpcqLAW3UVYtvo+yNs7Ja2nSe2Yo7ALdNWvqFGxM8DXia1j7WZmj0DXLoE6Ex7Zzt7GRM/BgfuFErMLZiKaSbx2nZkfmy+6PRmsdxYLO5ewPLPhw/dFZhX/4GqvT2cjcPXKki+KhkeiYHGnChoU7Ue3kWSRem5/1+fvFO6XTsMfPAwvSqcKGEW+RclC01nesQxolMct0yP0Vu91CbYSuR/e01EUYtiaS+g38WCZ3Q8aPJ93X9t07Z9inQw+oVb3EV0dXUbYzrJfdG1Sqs8poLX1CdPqxe+MNG5JMUECGrtX7xKIoCAcNU9v3AqsyU3FcsamskdeLiJsTNu2T+6M5Dg/NtDTWsvHo+yCwx1oWG+7PUGqR8nTGh2AoeBjH6EyCwUJ0/2SttNp0/+CvqkTS7eRD892RGMMshuNVsWI2Wm7XaCVgCagoDaLCC7GbftYQjtB/T+EPj0OthGcnCPCCHbuog5NU+lM/AaHD1jqsH/GSIjOczmBh5ezxVJn2IWsU/eg2waMpcd02qeGMXR6qaq9Tl1q53/PYwNkz19grF3jeRseuboCeKVjDXnZY9OxEKEPpaKzduh91KptwfRtusCWBEl9NZnkguUNKSpOhGGTO3Fl4ZV9axWaR2mVaV9PXAgyBy60qn7qEQ1eug5IJ4qVw0dl0SlocsgOKS9TrJjBRekqYwZGb3h5sLzu0buZx13jRs5IJSaBkY6O2X/BdKgUCTCOnP8+QjqqWddkeA9SYWc9qhdSwb08lwOZpa7vbSLuHyfYtGTo331LGxggk2BXgzB4cKtutcEi2bgIj1nZBimAayxoCcXUiszm33NGY2Z2U2veMKljzJZR7xf1vxGLxEQpAwl8JwEw/LX7m96uNgR7l5VFcHq3vhmlmeXhhh/iWPkTjZujMDJuabZF97hlbQmTW9i0vhl+vvnykpp8ObNZlINeQO+EaqBo9TX+lAwFra2yscVRLNAWTUimDHKtlV0UpIbkPdjEzhCjqqxve+6skbmIbsGV5+sHOE3ROcaqRqk6oXd4chclEr2HWP6UHoZ3asls83oC9sSfhmCX6r8pweIwD9TOkZdfIbu1smnJUie+69Hy7zffmWVFJiSwAtkJBdKOceSAh2WnVZTJ6u666HlPOCMwmj/NqBfyZ4oiJ9EzYlnzADUd+8W4Z0Ko+sLykKf/pqqoaSGhJWpvIuXGMPt1NnpDaQ1yz29a3S0U3OyWRMdKLrZqU0BZ2P9nv2nEqnHd4KNPVl/2T/mLg9qb1tX9msbXp+WywA1nc2B3Aj9RJBm2mmeN+R01eARVWq0iSLYe+6lr9aGT3t5TAe81eZ5/Jn95NawdHWojp1hzHYPBx8KSDM4ZMMH6G2TeOmIjZSKzwFgneRSB8aP0YcJJasZF+XdlGSSfjFkEVIEHwZVs+kFPlJh1ZB4y3R2DBkLOY1B3Le/kzopExS6Flsm0omuZFRty9rWwFPK4ZZHwENtfD6W+G/Uc+9lI258jbXbTAdk5xHbbKXLyV7kUSrwRdyAQG+UGHQiFxcrhHX/8Ce+7XCoqoGqaZ4A8jWnkPbzo3EkQO97ZFCofFbG4tvlxZ1z5XWcIoagWxYYKriJtvXyUnusqsSLPaS8O9e+lZvwq4siS94FO7eLvBDR0rlUe7uYn6EelcW4nNgKrk45xiI1zEWDr1WPEiwA0h7GB8YHr4sJpzYIv8FZwaHDG+3RA+WYdkKR51SJd2JDht1JviJlhqco07csQEPhSMA6FhfkHV/Iw7To66cjx6DwfLJRSEPumMD5RyHanCr8oesfFcSsQuYa3t4lybY/Bkn9zJmN+5dJKW0OnFB767peq0LyxQ44+4ZPOuvt1+R6GyFKM0izmSI/pZ2FtX2Y83YLGUlXP5XqDtrzSXKlu4BeedUdllLW5CNb/P9XWbFUyCY+sLTnCyOqrOQkvijkj8y0ekUQNxLJsFLC7xkuWH7dRnByB677uQy3cKAhKW0i/rmtIOrCTE2woHo9lDUG9gqjbUdrIrzQ8mpUa7mA+oA4aErazZZfkOthEfhreBMbSG/M+7MDnkLlW+5e6Gbh8ZKEefrWWxT6ycI5UYc2n9dcxnTvFEM9N9hoyRtltc2KZNebrjDIoZDtvhcaOvGsfvk20jYgWB77hPBxGYbiooZ3kJgm2rX/gWf92l44kn5WY92Tla6MCYhoOHz4BRjmd35IqV+dCCYmVk97aX3OZIOlpsVT62N1n/1HE4ABIfFICl/zC8ybHv13ml5e+iuEX5Xl39OuolN/s7k7gC+V0h9992Y8XP7t/j3TJCX6NmkP6jSsC0DIdkPPmxUSkdUwxxA9+6mRDHV1uz3P9qqIhtrS0sjEDt5SQR7Mi+6sdXcteamBobmpkYgNn3bzKc2H/fQoSo0M7k42FgAWwa3TuwgP39M1Kz3/L08s2bXmVtADWw/7xfJOLvOntj+9t6v1ca1sc+Qvj+L9gfnLy/9d/Z04r5/e/HK7KK+gVfMTMwM+8A45B/vO+YTaBLrYCefWuWjvhn6TOXFcbhSG/2eoAQzv7174w5nE2C/7Mkiu2bvJSYSn4xD68bCjvWlV2/qiI4jDSM4kdO6mXDdjNTuk6dPUNIsl/ew2kGJQnhdAQjN4BzXUi47L7TJJDxqZ7guMkYcLqHyHaTTLcit1PZM1KU1BmTRsZ3kFqjHGc4QEpYQw0LJtIMmHvUBGghzoIKfeN/jFA61vdg77gdx+nr8Nb0QsBK8biKACBncpUlsLiMV/jw/fO5ssji4zpPTKHVceXSSZQvCiRs3mwNUXqGOqEuIgJ38g4ZhZHi1VX9frXwDGWZ0Xz5qYf4/iGJrJ3tZ/KIJ6IBtMhXBRpZq/1QvJ2Or0LPF1Wd2oxaps0i991b1Ienl2jfKqdjQZluDldQ0ftchvBdJN7ZTOl+boIj8/mEzFUr9DscpKfR9gjuULcEquigq2+Fhy6jgPPuPMJfWGObu38A6rDPCqJ2yYkAGHRI867J22zK6dpt6BuKn7Sja1Bz3Xd8mVvE7ez1erw0P87gX1kP8lNJfyM9QCQ4DLO8rkpxz6eIZeC22w/exFUq1X/78Ll6ac9o0Udwmoo7/JdqAyd6+GEUOfG0osQWoS/CVyo1Y44YkFqmIXbTVn+q0fyGZ/mw3jZ09jZv0Tvcm7mpXGY+qtJhb0lodV8vohqQEItJ5G5bfQc18K7BuXOtMB5dfQatv+fcB7w8iiRv0RMNp7b6M89l6ozE93MHzBU53MT3zY9PZhlwtRza34kCdOBvSvWetlIUVlnq7lU950JhnhELe6o6oQ/sD+x0wie8S0puF7616sG/nm8nhIi1/NkJTCk6utd4mrlZDr1axafXY8dyPnCaM7tl4+ZewcmNUmdPTsaNgviPSp0gDyOPY/TXGShlDmq92b35829F0A+g99Ecofo9u5FBVql/zjc/67fBgMnXGzdJDqVXx3J6Oy+qVekGBgA/zwLW18tvk5wvOANa3cfhQum8YW4fZeiHtXmMy4ze9lO+bpcu8Ds5l7r3kJTM3xair+RCYlq4//0psj3zvfZ38Ftgc4cRljnUb5VgUh5XgP1Uv0QKQg26nbBXzaL8eonc4QLFx/O51pdJBlbV9vHowTyb
*/