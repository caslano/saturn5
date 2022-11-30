// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This computes the Catmull-Rom spline from a list of points.

#ifndef BOOST_MATH_INTERPOLATORS_CATMULL_ROM
#define BOOST_MATH_INTERPOLATORS_CATMULL_ROM

#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <limits>

namespace std_workaround {

#if defined(__cpp_lib_nonmember_container_access) || (defined(_MSC_VER) && (_MSC_VER >= 1900))
   using std::size;
#else
   template <class C>
   inline constexpr std::size_t size(const C& c)
   {
      return c.size();
   }
   template <class T, std::size_t N>
   inline constexpr std::size_t size(const T(&array)[N]) noexcept
   {
      return N;
   }
#endif
}

namespace boost{ namespace math{

    namespace detail
    {
        template<class Point>
        typename Point::value_type alpha_distance(Point const & p1, Point const & p2, typename Point::value_type alpha)
        {
            using std::pow;
            using std_workaround::size;
            typename Point::value_type dsq = 0;
            for (size_t i = 0; i < size(p1); ++i)
            {
                typename Point::value_type dx = p1[i] - p2[i];
                dsq += dx*dx;
            }
            return pow(dsq, alpha/2);
        }
    }

template <class Point, class RandomAccessContainer = std::vector<Point> >
class catmull_rom
{
   typedef typename Point::value_type value_type;
public:

    catmull_rom(RandomAccessContainer&& points, bool closed = false, value_type alpha = (value_type) 1/ (value_type) 2);

    catmull_rom(std::initializer_list<Point> l, bool closed = false, value_type alpha = (value_type) 1/ (value_type) 2) : catmull_rom<Point, RandomAccessContainer>(RandomAccessContainer(l), closed, alpha) {}

    value_type max_parameter() const
    {
        return m_max_s;
    }

    value_type parameter_at_point(size_t i) const
    {
        return m_s[i+1];
    }

    Point operator()(const value_type s) const;

    Point prime(const value_type s) const;

    RandomAccessContainer&& get_points()
    {
        return std::move(m_pnts);
    }

private:
    RandomAccessContainer m_pnts;
    std::vector<value_type> m_s;
    value_type m_max_s;
};

template<class Point, class RandomAccessContainer >
catmull_rom<Point, RandomAccessContainer>::catmull_rom(RandomAccessContainer&& points, bool closed, typename Point::value_type alpha) : m_pnts(std::move(points))
{
    std::size_t num_pnts = m_pnts.size();
    //std::cout << "Number of points = " << num_pnts << "\n";
    if (num_pnts < 4)
    {
        throw std::domain_error("The Catmull-Rom curve requires at least 4 points.");
    }
    if (alpha < 0 || alpha > 1)
    {
        throw std::domain_error("The parametrization alpha must be in the range [0,1].");
    }

    using std::abs;
    m_s.resize(num_pnts+3);
    m_pnts.resize(num_pnts+3);
    //std::cout << "Number of points now = " << m_pnts.size() << "\n";

    m_pnts[num_pnts+1] = m_pnts[0];
    m_pnts[num_pnts+2] = m_pnts[1];

    auto tmp = m_pnts[num_pnts-1];
    for (std::ptrdiff_t i = num_pnts-1; i >= 0; --i)
    {
        m_pnts[i+1] = m_pnts[i];
    }
    m_pnts[0] = tmp;

    m_s[0] = -detail::alpha_distance<Point>(m_pnts[0], m_pnts[1], alpha);
    if (abs(m_s[0]) < std::numeric_limits<typename Point::value_type>::epsilon())
    {
        throw std::domain_error("The first and last point should not be the same.\n");
    }
    m_s[1] = 0;
    for (size_t i = 2; i < m_s.size(); ++i)
    {
        typename Point::value_type d = detail::alpha_distance<Point>(m_pnts[i], m_pnts[i-1], alpha);
        if (abs(d) < std::numeric_limits<typename Point::value_type>::epsilon())
        {
            throw std::domain_error("The control points of the Catmull-Rom curve are too close together; this will lead to ill-conditioning.\n");
        }
        m_s[i] = m_s[i-1] + d;
    }
    if(closed)
    {
        m_max_s = m_s[num_pnts+1];
    }
    else
    {
        m_max_s = m_s[num_pnts];
    }
}


template<class Point, class RandomAccessContainer >
Point catmull_rom<Point, RandomAccessContainer>::operator()(const typename Point::value_type s) const
{
    using std_workaround::size;
    if (s < 0 || s > m_max_s)
    {
        throw std::domain_error("Parameter outside bounds.");
    }
    auto it = std::upper_bound(m_s.begin(), m_s.end(), s);
    //Now *it >= s. We want the index such that m_s[i] <= s < m_s[i+1]:
    size_t i = std::distance(m_s.begin(), it - 1);

    // Only denom21 is used twice:
    typename Point::value_type denom21 = 1/(m_s[i+1] - m_s[i]);
    typename Point::value_type s0s = m_s[i-1] - s;
    typename Point::value_type s1s = m_s[i] - s;
    typename Point::value_type s2s = m_s[i+1] - s;
    size_t ip2 = i + 2;
    // When the curve is closed and we evaluate at the end, the endpoint is in fact the startpoint.
    if (ip2 == m_s.size()) {
        ip2 = 0;
    }
    typename Point::value_type s3s = m_s[ip2] - s;

    Point A1_or_A3;
    typename Point::value_type denom = 1/(m_s[i] - m_s[i-1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1_or_A3[j] = denom*(s1s*m_pnts[i-1][j] - s0s*m_pnts[i][j]);
    }

    Point A2_or_B2;
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2_or_B2[j] = denom21*(s2s*m_pnts[i][j] - s1s*m_pnts[i+1][j]);
    }

    Point B1_or_C;
    denom = 1/(m_s[i+1] - m_s[i-1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1_or_C[j] = denom*(s2s*A1_or_A3[j] - s0s*A2_or_B2[j]);
    }

    denom = 1/(m_s[ip2] - m_s[i+1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1_or_A3[j] = denom*(s3s*m_pnts[i+1][j] - s2s*m_pnts[ip2][j]);
    }

    Point B2;
    denom = 1/(m_s[ip2] - m_s[i]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2[j] = denom*(s3s*A2_or_B2[j] - s1s*A1_or_A3[j]);
    }

    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1_or_C[j] = denom21*(s2s*B1_or_C[j] - s1s*B2[j]);
    }

    return B1_or_C;
}

template<class Point, class RandomAccessContainer >
Point catmull_rom<Point, RandomAccessContainer>::prime(const typename Point::value_type s) const
{
    using std_workaround::size;
    // https://math.stackexchange.com/questions/843595/how-can-i-calculate-the-derivative-of-a-catmull-rom-spline-with-nonuniform-param
    // http://denkovacs.com/2016/02/catmull-rom-spline-derivatives/
    if (s < 0 || s > m_max_s)
    {
        throw std::domain_error("Parameter outside bounds.\n");
    }
    auto it = std::upper_bound(m_s.begin(), m_s.end(), s);
    //Now *it >= s. We want the index such that m_s[i] <= s < m_s[i+1]:
    size_t i = std::distance(m_s.begin(), it - 1);
    Point A1;
    typename Point::value_type denom = 1/(m_s[i] - m_s[i-1]);
    typename Point::value_type k1 = (m_s[i]-s)*denom;
    typename Point::value_type k2 = (s - m_s[i-1])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1[j] = k1*m_pnts[i-1][j] + k2*m_pnts[i][j];
    }

    Point A1p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1p[j] = denom*(m_pnts[i][j] - m_pnts[i-1][j]);
    }

    Point A2;
    denom = 1/(m_s[i+1] - m_s[i]);
    k1 = (m_s[i+1]-s)*denom;
    k2 = (s - m_s[i])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2[j] = k1*m_pnts[i][j] + k2*m_pnts[i+1][j];
    }

    Point A2p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2p[j] = denom*(m_pnts[i+1][j] - m_pnts[i][j]);
    }


    Point B1;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1[j] = k1*A1[j] + k2*A2[j];
    }

    Point A3;
    denom = 1/(m_s[i+2] - m_s[i+1]);
    k1 = (m_s[i+2]-s)*denom;
    k2 = (s - m_s[i+1])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A3[j] = k1*m_pnts[i+1][j] + k2*m_pnts[i+2][j];
    }

    Point A3p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A3p[j] = denom*(m_pnts[i+2][j] - m_pnts[i+1][j]);
    }

    Point B2;
    denom = 1/(m_s[i+2] - m_s[i]);
    k1 = (m_s[i+2]-s)*denom;
    k2 = (s - m_s[i])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2[j] = k1*A2[j] + k2*A3[j];
    }

    Point B1p;
    denom = 1/(m_s[i+1] - m_s[i-1]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1p[j] = denom*(A2[j] - A1[j] + (m_s[i+1]- s)*A1p[j] + (s-m_s[i-1])*A2p[j]);
    }

    Point B2p;
    denom = 1/(m_s[i+2] - m_s[i]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2p[j] = denom*(A3[j] - A2[j] + (m_s[i+2] - s)*A2p[j] + (s - m_s[i])*A3p[j]);
    }

    Point Cp;
    denom = 1/(m_s[i+1] - m_s[i]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        Cp[j] = denom*(B2[j] - B1[j] + (m_s[i+1] - s)*B1p[j] + (s - m_s[i])*B2p[j]);
    }
    return Cp;
}


}}
#endif

/* catmull_rom.hpp
jfqWTn2h+JPpfyNeuChpafKIs7En/5zMDwAz/m2HR2I+HAqtepsPvgpOZb9vJn2x+D3fUMDSsfS7GUp4j7fNGhfpIc3N4oX5ibMCzXOhkIPDt2Q3hlVNhCJVt2RyLfe27b9JO7XeiGcptagwvlx0Y6pJOBMKcDRULPTitE+XWQz5ulNXExikfT2vc+3vgaifDhjOwgt9ljijl/fCSXzFRduggVOhbo4O+NOFvb9tXe7M1uf/0lcE/fyIOMiPkZa8DQJPASEtmBzTQa+dkfBa6su7P1c1aR2Ro7V8GZjFmryMUj5vb6+j/JXE/atH+GQ284ThKSNVubzOFbswp7f3uup1aUfX7zSZ2jJLes+qUX8igNqz2ICduBi9AiBoNX9kcogbEyOMAD1jXO5+hVHnZ1bS4t++wkl7mH2RFg5ody/SLWJeMF1J6pSEGTkfwG8jQOEHPWiyWFApowumG4MeBhOq3RAieUF5ZwP86sobmnKe53t8Q2g9kRlySKXcovMBxx1OWoac0ushr0M5E0MObYnDpxs/R3fJveGibTfByVI7/QiA9E0MkyCOFQ78iH/M7PvsG61K+9+j0gBI7moxNvEmDbXbbcjNVo8AKuZxUsy8HDU2QHAVevHRqZsvuoWPnV1GbmvZAw2qbjtMXoW+CUeFzIrQSWK/uBNlYz82QWX5a8hCSzYKzo4fomyz82cgF8tR1PbUZRnXbh+tEQePj8Yo+3hmr8fZquHvKhw92Jg3HSPHaF1YzLwNH2CYAE8UPYcJEjZtD5Dbs7tD7ugDJft4Jhn55317bIVyB2Co4rtb+GGycF0KT8pEYswbs8f1c8N8sROvfune1IrFZ7XI6I/DRQqW3s7iOOEaKcN5bmycG9iNsVnnYXlKep5BEW4e7So97WEMpIdzukVRsDSRegf6RDpUoyUL3k96vFY2CvJJTQUW8PDqK7y8fNYSAfgzfk2ttqnOVTKXhcOjbNuDP/Tx5zIdbUjI93dYKDiy+qmCD2kRjEiVUYlXqpentdflg9MnBzX8R0x1BEQkfaKp/xZ+rAb6+pQ1DjACwmtfdqI3Uo99uwoXrNKCbihkx+pO6xZ0ybxEqlQ1gFN0Jr65d85nVPFH95En64vvY6mtQukqaixuBzNbvbn7ZBGVim9ub09aLasJRIq2OEaAORSOu8mDIDefC3qEgCIh7C3ZYROe98FVbJDUOW+XmDbgTMYp33JcZSNjJF4YR+K6sU68k+JhTTR+92AjygvYWXJVvPf+i+jAaYzzAcfeuvbZoJLw6RjbaD3KSk2+VyU0vXk94hVOyF3cE2xCtLbpFinoi+udCOvgVZ1zY4q2EuEQi+kocZY1XdovUWw10E6SxXzEzHKgUnnDnnx6BQULbth5XBthc/fWWWWpDKJinGF8ekGhWzq98RqwK1XgziIny0qhf2scrwACLP3Tft+Lncxf8A2q2Ou4WVyKR4nf9ZbCxTH9LP3H5dFWuuzjUv+SU2G5ZXWyHVkhlHVGbbotWsDtC2ynarqrN+1JpxeLsYqzmINohx6cVDII2y+43VGdVn3l6EKGRMolwcryXL5zj4YmJj0BnG6j8zUMBTiom4paoRMtQcNgCmh7epH8nJZNVm6xo5gzdW203TGidQvLybT5k/APSPrZ3CyzGzIRXdJoYfaUl+AOBvDbmrukefDGHr6wNcnqjAUh518FDHTDfCJojzRV3GWmhkWfnNY2OqK3/eO36kNdK68GvmXhQcGpxDA+M1PPCnSaaMJyl16FATQluXgAwtFd+lNHxe30AwOiLOQyb93fUEROspeoSNCV3OG+uxvI8hvujFp77ddyeD47AYbDKvowh8ZlISnhoaOWg7Dxde+NhkWdJ+4MVEPfs+nFCbTcRMofWJE8sJ2z8bwyVsESXlRtMy8qIcfZgOXjdSB/P3Si0TxDNJK/hFPgmn2KT4AEncBFmqGf8QaTacLwhZvUrZCgtGPz27fmR5WUZ8N0x0EtRoc7hrsULcR1F0fEyorQ/Sdfzh3EZJSh7kBHl5VDM7Ml31tZ2FcdZWb7mw4osuMZiwWh31xrRUy4efpGWLUSRle6lICibxfN/jQJM9NPVmfK+MuEU7rXniX1YtRM3Dl6CyrY317tOAcS1BA3P00MxEb/EX5Tgq9x1EsBZKL+99UXhBj2IA8L5JCypikvoc0tySqKRBN6AF1I4+Dyc516b0O+jUbTFHyTpCfnTqW7cARGK1j+1PBBa3UP2CfwYkfoTZ4/yIYi0zudlTFw0aIgKhiyr6WI2Qn5NIaifYkyaADA8CKM3WaT81M13eiFIHaZFHNu7JC5O+0Kvoysvr90TZtYvaUf+89YtJWs+AUpCzNocDqn0LD3XyaDfjU00gXdI1OK7KR1JeNap/tl5shEehrafHKUipqD7SQIZNiNE7U90DjPxDOjqmWlJOh6ppnRN2iW2Ew2x4Gt+9hBRraBzJGUov71a3HRgoA4pTbeyXCFlXah1l7rtSsy1VMaV2w9A/PxyTyR4MxCNF06tczm+iiz+zOozvJUGJ/VYChilKp+y4dafb93VbK4OZzhehRhn5GViZnbo/R3zPQ25pQzTDFTdnGt0w1gZisM4zrnJe2ZshwzpH1iyB3dUvKKDsKONEzXvXAjQBoaXwfwIg4MccvPczjPNluT+lz9pn/NLBoG2zFwZPNAXyja7f2GCAWJxHoBC9uipjrp3jJ+mUzK3pZmHU4V4UuvoSZ7GBgrq4LfOKH/kOXi4WXrMvJsSnOcmFR2dgV2uqUDEByEFRkEhY13rhf6aTF+TGL4r3KYiWmNWtA7IKxQ5SdWY0FgFQAhM0Dff59KJg5gERitBIX5KPU8g7cKch5ykF5kFnDRrauxHDqRnEzp7GwBIDNeEHRBPy0StU8vjxG563WMi02v9RA5Jiedu+g0oCcDLYT3is3LSka7dE09Fh0qzdr4C0ZDRZnHWC2klQz3Rw4SlURU+cymKqYQ26TbMZvotTZe2Vv40Lwja/NhwkCyAeCNZiYlhAIWBL1U9Q/QtBwwjH2LJADteXzmx0/0cHCNzIIsKmNt3OCHXHA8w+a4QHztJSR7xCsamtcursB8E3xzPJM61Lta+7BtxyQto4OzeVDY4oeZiMhQlXWB5T9StPaGFOVdmaFPj7flOU7hWz3ob4g+hmFJbGXTIqg2EitphQdbM90BcRwMYx/VmigUejjWhbKVkvmv5FDe77GnDuzzVlXDIyTflhKeHSt4LSZi9H18GLpOW9MmxPWT3o9izalVWcBsUKs8TNOMmmdQziycEU9mfO3662VACfy7APdj3mLhEjm8yxLB+t9E7pNSNLOPAEz2pZXklTCxBDEtaCOJJQn+LjPup7ce9Zt1Ty/X85RN3r0efMCZmdGKcyF44QTCDfXohg1yDR1T+uJs1VaXZWcvtlyJ55iWzrDLCgfrhzUBW8QrZxzrZsI/KzDzMclhazPBCdGqU/tky23cClnsgdch7ecDQ9ugApI2DqQnKa0q3L50YSWsWqrcjVXjYfOhNYuxhQgTGJMHDclrdNYb7k6x9WRTNuQd65ojZWbLZyVz5DOaRvWEB7R6aLZYrjAXNDgZ7Z/NyqUGeMnIKlapI1h0LEpqkdx0HwmKgLXQNvLVREZ20RWepuFzVWwTc9FZztjY1FvnxOWBBTXa3FuMjmAhZtN1RIKO9DUTk6mMedkjSw79sdwGG5uHCqS8z8oKRzTIeKZBMvD4XCS6062XMV7N2jU4hMMdN9Yx8ElXMq1nEd/BdN7dqFr/lYGwB3ehU+Ss9Vwa45uX/EvOd5qT5fRrif+8xY9So/JrXaNbDJPXUP62blmpfGQ1XXKOZa5Nf5sNhxsLGE3bQe3AlpV6rp7ZQHdoAQ7vkhsEncRN7X0tH2f/1E7kiIXfDexVlOpQ15BSWT38j15ibZ2Qpa9Zul1CqqFlUdWZvmBoGQMrSTXsyMQmZp5T2rsceaShKI3yl/n2221VzePj6jXJm4Aw/aP3nURI4jrYodMpfqNT4cJSUb42sen66aXJgx0dmE4do6yP1nCUjypNZj59wy63LGBmfDEX8Blp/QfTuy2U9+2ze9fPvOq28W1FEkHmWo+Vy18afE/noAC0zYST44veb5j/vME/oyVyPyNTba58hRHC/t8rFnUL+KwhKrfFt/keIDbxIIyheXq6PIMv/zUdVSAAt/e1B/8cCa1MSvMgw7MJI8TaNDF8fJm0Lm5NQ0vNkKfXv8YMli/eeuk1L0/1H3+FaMmIh0OkG++aWD8YRkyN69naF9xDXf88/I4GOKzcIiBj2hQ8X9MB6Dx4CeSVOQbzKXvu5o2HlY5vlbZXnFbUByWQJi12a7p+HmXn9U6iVnKCgOrPyHGDAl4DV1pmU6hJr5pB2T2YIJY5xpnL239sMsfLHb5pkGfQiT4LKR3aCLzkVdHS1CyXjQdhfuFysgqIznVkCmYkn6wf2+qtc2y94TyI0brIdTwylG3CI8Q2a8DHzQM7CIH3Phv27dPbbpYhNwvl3yS+52uJTWkdgIIljjLdWGzkM17/Dm9vEseTd9NPThuNXDgaJ9ahHkLkE8K6Jx6tr3eHcVR0xQ6zEpH1OpH0xqpW9RTho1Ujy0DX5aLkxpUqcf99U9xeI6z3362uD6LIIQ6Lg15ULy934HwQECkVPaQpP/tqQb5egYF4c47zoBGqVMF8bPRQyMX5OJ6jZKMhAdgGvUX08PZ8jJWXMjY7muRmRFe3OH2q46+OmI/KW7MUQV+rts5Lpgam0ZTYO2f5W3qWWn1b0RwI2Htbq3n1r5F4cg+0rareumcFXu+mWS/4JG1LVApPM4tp3KB+OlEio2WXo8X6bgwmAEP8jHCGg+Eqs0cwEk8lADZrsL0Z7D33RxlJ9bldYSzUgrewaVa0qF2C60yoEiohY3lVZaYURi7gfvr4YjmAcMA/KnvFouK96sxEPNqlprrRhTaFO/Cr9EYxi7zc97IgsxT26OwnYf8w0JcEcXMcXfs6MFlnhPtV3V8xfBL0ir4mbL2RUshJHizlqwYb/XT7A7XRn5RAevXt9xPMG+B/DCfi4IWZK1pvy8STL9vEl5csrUNjUCTIoC42VWLEY2NPbNF3I0rFL8vhWPT35p7p1ZCP6MyuEjIWjy9+QOvqewZW55sOgr/ZR0CMBCvPYtx34ALNlcF63OcaDbZb2/E5OY8ILFqu1pWUBvDTvpInmk5feCLAo8DNxnxV98NnfBSnYF+L0AAAb1vbuFQDLqJV3cbsANTaC09H0ZsXLikKdPqaR1GViP9LMW1wM+Raqyr7zFBIcZLF5jMP49OB6v+W/S8Hytm1aJtkuIgbXBuKHcvC2eS/lbBct3FP2oG/2KrUpbw75kP3m82mG6X0NV5Rsq3C0V8dqn7L/ZMrexwLfyvLMa2UE23v10W6F3dxJ96y+Gc9EjxrhJmFG71GVuipOKrM5McM0k2Q4Yor4LfHbeFYR4yLc//jYKySl5dvrDVfHNG4ZAB9qFszwYPqf0P6Jn1XwLxnjqWmHRqka5d9u3pMRZOPrHBgRkAA+DtAIAAoAAD8ABFSoiLJaItEwasWE7QhtJY1oN4WWpZog9ChWhC+86tazc2rD0Utv3PGhyLEAKIAAAYAdvCfNABbnXzQ9ZF5CGyr4OB+gon+s5eAMgQC26b0zgkgleO99quaqiu9PejMlRO+vZQMp1RlHNPJCViPK5bhmMRFK2FwTWQV/TjXDJYR/UwNRYlkQvk/EgFAAH8vw8IsJwIA6rG/7pqent5pnVIasVuJjA+mDDVKo2ihDaC4IyiECKAQEgoBGO4RACLJJpGUIwAwSpRDdBf3yIn3Heyij48pY7Fp4MYvIK1w9NU9tHwRBC24mRZTYDIwz6lI9xoBe/aQTI0hdRXtgW0GnMed91Mn49NWWJJdJxcFrMGEdgpWp8ECctOs3Fs7kTrsB6h3Y3cC6BvWNfchKzBJd68l4LvZvJpgm0DebaoOWjssifikr/DqwRnY6wtumFpYNavxo8emtR21p4DQqcTn+9h9Ba2mTNlWC5e+pWWUJgi6GVaN3SAkIsMk1xVWVCaTGuk90XVrbyAaaK51G74Rrxvzj8vCAeAomSjqFdXxH7XLFkKYA7i8djOdrX22d9MqOAQmAzoavvaSxlzw4TMoaIofF/ANejlLIYBmq8tKXvoMBAzqGa6v2FzD6wYHBN3oKwuKkQKHOM89YcMoF3GZHxRWSPph+bRY8hfMM6Ha9UDD1uS4y+M2IK5XSxlelDdqq0Q7CqhMDHY7B6kODgdeGIbtgqplSj2KgUpmjDtDS5Uw62OtNuTDKMeILVKgxumig+F96Cx8OM84GqfQVHgP7kM+vMmFyOCsFBZ1Uc7mh3umObGWMpMUaF+v6j4QZJUYIHcowfGQwfd8PZwzyjfWlfILuKsrrh+eXhmloZgywAhqwZ8ocLMRVgpxwYB7+6jX3LX9sK0yKt1yzcbW4vr9ZR58xMYydHjSycaDHzeNvy778jBppOUaf2Of4iyK9EBQKD4P5iFn8pV2HPaHz3EW0eNeVu87WBUtKxA0bwSXKiHw5wZJyu+rnCqfqIulxFA67683sJZRHvBKqO9ai7rd69ZiPjmTu+pqylVBpNW4t0x74IAzMciVjppz6HLXRtv51z4EVM/dIMLFuQ3PRB5sw0pDgoXBMhWpCmjFeebBDzzh1CmebBbUCW9+n6XB62oYm9NqFL+7NN3PeRFdrJ6FfAuKMjRkRgvUBqXtPrWWnOgnNKnWuP0A04IbNFKmBSgiTlaSHf88L0Tp2tdMDUwULJZhfTa6xDic3i25yCu3e7F5GqwtysrZkixfPJoL8rPK3pilQG5ATkqSALOb74GckivTCKEgznC5t2qCHfvuEvq7CYRJQPA+yU91J36yt+m9aPTzIk+KXZKvXz0HXdIXLqTmZPZD7NbnjgpO//sg5TQxfM2kvBJ4kJxp0YfUa6cN8Oi/TOuMvyQAUQVUUo8jq5QWoizdv3eP6XpWMWYcOQKEEWfUI9eGePx7EHQedfKlNgh4xAbEpop3N5AJwYOObO/Yrr1uezWYc0oOUBLjtOKBKRO+YV4xO9uhgDUcWD6129SmYyfs1QwEexQK0dE4GdyvDpQLnBCv9Azzr6TCfZCgwteLLykf4ETDh78qTTFNMUAGOK4aUFHr97/s7ntnKWq1fOC4WkbLTRj7rnEswc1B4cvGkOZPGWtVKyGWOTyu2SFouX/BAgFr3illquHWX3yiaoi/D+IF4xwe6EFLoTHsD7KWY6Yx01CJKrq6uEGnD7hszcpqkUywKpIOg+tPgAVlTR9MUu+5w1U3RGltaluOPSX04oor+6pdG5izVmLndz3HKphCVOR5c3DYQozMtpsUGowy9RDTWEj+iYCwF/k2eGyzX59x/N61U4DKxnQrcHzRB+JKw+9nw1lQMNED0eLuSyosJ9T9G4J1j257P2lOIN2/9dPvv4LmiNwXSIwpldo1d9JIvCnLuVG7MQqfz144tKxFIzoJVoYyVQ4mnuL5eXGS1gdDWiSFFBVvvWFWeh3HGkelJWoRDc6EWSBHwIpLiLcmWWtBy/T3X0nxQNtRhCqoBhzbEBTxofi9NeciY3DdPiiClZ7pbeDWFw0v
*/