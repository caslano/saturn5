//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_STACK_HPP
#define BOOST_COMPUTE_CONTAINER_STACK_HPP

#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {

template<class T>
class stack
{
public:
    typedef vector<T> container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;

    stack()
    {
    }

    stack(const stack<T> &other)
        : m_vector(other.m_vector)
    {
    }

    stack<T>& operator=(const stack<T> &other)
    {
        if(this != &other){
            m_vector = other.m_vector;
        }

        return *this;
    }

    ~stack()
    {
    }

    bool empty() const
    {
        return m_vector.empty();
    }

    size_type size() const
    {
        return m_vector.size();
    }

    value_type top() const
    {
        return m_vector.back();
    }

    void push(const T &value)
    {
        m_vector.push_back(value);
    }

    void pop()
    {
        m_vector.pop_back();
    }

private:
    container_type m_vector;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_STACK_HPP

/* stack.hpp
bPzRdOKTHOKcMuK8c9hLb+zFp/gPziOE/TBm/H/Wx+gfcdj7lcQpnZN4bgL1zQ85T97POFCN328kPtzFfPHDTpBvlY7wfAEf9DD0Rsd38cPEDe43o1ecIb59hLzxLt6/cQp/yHsU2izw+6xTm2+pr35NXwF+4Pge+iE/I16lz26AuK+ykXiMeWMThK7oh5/GnhTs5b4z3o1vMn8/JO4/Z8X6pC55JbotcY6ZdRRYit7mR92ceCvkN/Yj0D8Qciv7BufxfNW/eO/O99wvM3nWUuK9HvoFiEv23UY++xF22JY+W/rj/HlOZeNPxPnkeYm+jIt5CvoOfmYV+dga/PSb6A+fUI/A/tvP4PO80IW/5LjPM16mKei5jG8n8/wH9C5b1gt9BQerWZc+6NsprBMv9Ep/9Cvsm//XzIs/WUc+nFc6eWwO8/QexpN529ZDPP7TJOwUdc4dzP9X8MPkGwHoA8eP4wfZx3iwm/nzLPsImeepw6zLY/S9voi9e47rwy74o+d6tVJvyWCdWbJeXkMvQkf3S+P8rplC3M11029uRgf2+c7EOFPHI56O5Tl8CxqI1xLom80iHvqVvOtt4pf3iN/vpK+WukOEN3atkLiL/CCvmX0V9AFmdPPcH+IZG+JxV/KViHL6MtA1ho39jOuJ/3+iL9GMfZ7HfJqLf19KnJeFf7BEn7qIuPZW8soK8mPijgXtzHdv1m8e62wmccVr5AO52EHyrT4jb2a+x1NvalmMPUDvrGujLknfXzHvFXItwK5Qn2zj7/f24e9Z72vHmS9t/Mn5eZDfJB0ij2bfYuI58qv3JuMneP7bffRLE1e0/UZ99QWuZxbz+wjjfQ3jQ55T3ML4k2dnXEqcsY24ivtpJt5smWKJ3+V+pJMP+rI/EL/m5UB9gDxzy2N8/hP0heRh1yzRZ9/i+wPo6uOs7/fM6ET4lVtZX19iB7azT2Qmfp95XX891/E143YHOusIeTbHibiM+dnGfPt9En6a+Id9QPt8qb/8hq6Riv0spQ8G/cMVP+sRj79G1wmZR17VQdz+FnlYrzV65MT3YztY33cyHldS/2A8eoi7ttzCdZ3F3rXhLyKpj24ifndAr0GX63Pj6xH8Vz7jyP4PUxp+iPvejP1qYd010i/UvQE9bCs/R15bT32uO4t8LIM8nOtORefMmW0mTjD2aeHfv0GfD2EdYYey3pjKcwZZ5/SNx6ILjA3Qd3c7uocz/vEF5ssW1h/1spCjfO4TjOd/0VWpHx8kTgpkH0voDcTb5A+HUvEn5A+xPBe7p5nnKjVhz7j/3QO8p8HonzPeyxeIfeK8d36PXSce20hdqvRP3r9EXpGVx3Wg2wZMZZ7QFxrij67E/uBGC+LTSeQP6YwHelIlcUwUemLoXexbOoxf/ZM6pi9+pAo7vgl9Bz8R/xffp+7lwXr0xL+W/sj5tlCfnjqFugD3y5U6ch12bzb+7Ft0LvTVEPoBQ6hfmzqIb48wf9gfkn6WvowR1sly6qnMh4JGdIdm4uQZ6I7kBWsPYk9CbOmjR+/4eeL4eWbOo5U8fSl26Glb+m7Qtebjx4hfHNPQG4y443f6sXdSh7JlPxrrwBl90lzEeptFfvsm85S80Qf97+Tv5JNj6K3sGxx7gLi6i/rpm+T736ErkWfVd1oxftiTe7DjGczPAOqGruiCXsQnuYz3ZOKlCPoDHrCk34x+QfSkjenoBjbEiSn40yfRfeZQz28m3v+QuGoX/ae/Yl/Rgx1fZf6fJd+w5b7fT511Ev0w5MWu36GnELd6Eo8NG+85uthuYr4HYyc98N8L6VcdsUZfYF/N+1x/EPPa13g+MzpgIv2iX6FLcdwF2LXST+k=
*/