// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Alex Breuer
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DIMACS_HPP
#define BOOST_GRAPH_DIMACS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>
#include <vector>
#include <queue>
#include <boost/assert.hpp>

namespace boost
{
namespace graph
{

    class BOOST_SYMBOL_VISIBLE dimacs_exception : public std::exception
    {
    };

    class dimacs_basic_reader
    {
    public:
        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
        typedef double vertex_weight_type;
        typedef double edge_weight_type;
        typedef std::pair< vertices_size_type, vertices_size_type > edge_type;
        enum incr_mode
        {
            edge,
            edge_weight
        };

        dimacs_basic_reader(std::istream& in, bool want_weights = true)
        : inpt(in), seen_edges(0), want_weights(want_weights)
        {
            while (getline(inpt, buf) && !buf.empty() && buf[0] == 'c')
                ;

            if (buf[0] != 'p')
            {
                boost::throw_exception(dimacs_exception());
            }

            std::stringstream instr(buf);
            std::string junk;

            instr >> junk >> junk >> num_vertices >> num_edges;
            read_edge_weights.push(-1);
            incr(edge_weight);
        }

        // for a past the end iterator
        dimacs_basic_reader()
        : inpt(std::cin)
        , num_vertices(0)
        , num_edges(0)
        , seen_edges(0)
        , want_weights(false)
        {
        }

        edge_type edge_deref()
        {
            BOOST_ASSERT(!read_edges.empty());
            return read_edges.front();
        }

        inline edge_type* edge_ref()
        {
            BOOST_ASSERT(!read_edges.empty());
            return &read_edges.front();
        }

        inline edge_weight_type edge_weight_deref()
        {
            BOOST_ASSERT(!read_edge_weights.empty());
            return read_edge_weights.front();
        }

        inline dimacs_basic_reader incr(incr_mode mode)
        {
            if (mode == edge)
            {
                BOOST_ASSERT(!read_edges.empty());
                read_edges.pop();
            }
            else if (mode == edge_weight)
            {
                BOOST_ASSERT(!read_edge_weights.empty());
                read_edge_weights.pop();
            }

            if ((mode == edge && read_edges.empty())
                || (mode == edge_weight && read_edge_weights.empty()))
            {

                if (seen_edges > num_edges)
                {
                    boost::throw_exception(dimacs_exception());
                }

                while (getline(inpt, buf) && !buf.empty() && buf[0] == 'c')
                    ;

                if (!inpt.eof())
                {
                    int source, dest, weight;
                    read_edge_line((char*)buf.c_str(), source, dest, weight);

                    seen_edges++;
                    source--;
                    dest--;

                    read_edges.push(edge_type(source, dest));
                    if (want_weights)
                    {
                        read_edge_weights.push(weight);
                    }
                }
                BOOST_ASSERT(read_edges.size() < 100);
                BOOST_ASSERT(read_edge_weights.size() < 100);
            }

            // the 1000000 just happens to be about how many edges can be read
            // in 10s
            //     if( !(seen_edges % 1000000) && !process_id( pg ) && mode ==
            //     edge ) {
            //       std::cout << "read " << seen_edges << " edges" <<
            //       std::endl;
            //     }
            return *this;
        }

        inline bool done_edges()
        {
            return inpt.eof() && read_edges.size() == 0;
        }

        inline bool done_edge_weights()
        {
            return inpt.eof() && read_edge_weights.size() == 0;
        }

        inline vertices_size_type n_vertices() { return num_vertices; }

        inline vertices_size_type processed_edges()
        {
            return seen_edges - read_edges.size();
        }

        inline vertices_size_type processed_edge_weights()
        {
            return seen_edges - read_edge_weights.size();
        }

        inline vertices_size_type n_edges() { return num_edges; }

    protected:
        bool read_edge_line(char* linebuf, int& from, int& to, int& weight)
        {
            char *fs = NULL, *ts = NULL, *ws = NULL;
            char* tmp = linebuf + 2;

            fs = tmp;
            if ('e' == linebuf[0])
            {
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ts = ++tmp;
                        break;
                    }
                    tmp++;
                }
                *tmp = '\0';
                if (NULL == fs || NULL == ts)
                    return false;
                from = atoi(fs);
                to = atoi(ts);
                weight = 0;
            }
            else if ('a' == linebuf[0])
            {
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ts = ++tmp;
                        break;
                    }
                    tmp++;
                }
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ws = ++tmp;
                        break;
                    }
                    tmp++;
                }
                while (*tmp != '\n' && *tmp != '\0')
                    tmp++;
                *tmp = '\0';
                if (fs == NULL || ts == NULL || ws == NULL)
                    return false;
                from = atoi(fs);
                to = atoi(ts);
                if (want_weights)
                    weight = atoi(ws);
                else
                    weight = 0;
            }
            else
            {
                return false;
            }

            return true;
        }

        std::queue< edge_type > read_edges;
        std::queue< edge_weight_type > read_edge_weights;

        std::istream& inpt;
        std::string buf;
        vertices_size_type num_vertices, num_edges, seen_edges;
        bool want_weights;
    };

    template < typename T > class dimacs_edge_iterator
    {
    public:
        typedef dimacs_basic_reader::edge_type edge_type;
        typedef dimacs_basic_reader::incr_mode incr_mode;

        typedef std::input_iterator_tag iterator_category;
        typedef edge_type value_type;
        typedef value_type reference;
        typedef edge_type* pointer;
        typedef std::ptrdiff_t difference_type;

        dimacs_edge_iterator(T& reader) : reader(reader) {}

        inline dimacs_edge_iterator& operator++()
        {
            reader.incr(dimacs_basic_reader::edge);
            return *this;
        }

        inline edge_type operator*() { return reader.edge_deref(); }

        inline edge_type* operator->() { return reader.edge_ref(); }

        // don't expect this to do the right thing if you're not comparing
        // against a general past-the-end-iterator made with the default
        // constructor for dimacs_basic_reader
        inline bool operator==(dimacs_edge_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return arg.reader.done_edges();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return reader.done_edges();
            }
            else
            {
                return false;
            }
            return false;
        }

        inline bool operator!=(dimacs_edge_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return !arg.reader.done_edges();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return !reader.done_edges();
            }
            else
            {
                return true;
            }
            return true;
        }

    private:
        T& reader;
    };

    template < typename T > class dimacs_edge_weight_iterator
    {
    public:
        typedef dimacs_basic_reader::edge_weight_type edge_weight_type;
        typedef dimacs_basic_reader::incr_mode incr_mode;

        dimacs_edge_weight_iterator(T& reader) : reader(reader) {}

        inline dimacs_edge_weight_iterator& operator++()
        {
            reader.incr(dimacs_basic_reader::edge_weight);
            return *this;
        }

        inline edge_weight_type operator*()
        {
            return reader.edge_weight_deref();
        }

        // don't expect this to do the right thing if you're not comparing
        // against a general past-the-end-iterator made with the default
        // constructor for dimacs_basic_reader
        inline bool operator==(dimacs_edge_weight_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return arg.reader.done_edge_weights();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return reader.done_edge_weights();
            }
            else
            {
                return false;
            }
            return false;
        }

        inline bool operator!=(dimacs_edge_weight_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return !arg.reader.done_edge_weights();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return !reader.done_edge_weights();
            }
            else
            {
                return true;
            }
            return true;
        }

    private:
        T& reader;
    };

}
} // end namespace boost::graph
#endif

/* dimacs.hpp
b3S6aZ7evG1ogoAgxlCm8S2QOJpbgXii+57y8Wqzv9jNLBQ/Y5n8FvG5g/4shMVNz5zj9vtncxq3cqkZxUJrxt2USO6t4Quwv4A5vMBa5NbR5PIHgpcjBbxvb1bttjhvbGS5jVsOEXsCIzlFhMx+uDUJbPwKj9gWzlNgb/vZgbp/0XrTEuXPbvij33FTAuXwBNgmTKRiRtaKMTWfAJIUZ15H5AQ8s9cCkFEpzZr/zbkejTdQ79QZEkPxamHlmVLCJPJE0sss5djn0MBw9xb9Sg6ex5gWhSEIDEDdxHzFD6PRdbF613/xXaicUKVEgcthAydUBJPkk6y7JUi7N+J+E4U6NoFHb+Pkmye8khfuT5I0GHo+SZLF+k/ViiRhZn6dJHwm46pKWKGTI+ax3n2cfMI3u/Hgo/sqWrQEb2mJqpot5NeBH/o9PuAp8kuvTaIB4e07DQEj1puvsHpA+8JFiIbVzwWqxZBx5PVt+RiPG9T2WJM1PlaqdlPCz0ArnCiENu37+XD7ElaoZ7HXlhmyD3P3PtX0wp4X1Rfuti+zEoO3GsqFQgNguy9NGX9eK1snTW922MJpeREHg8WJhteMNbWb4Zvg+ABTGchP5ZEFGMBGEWvk2nwunhuJKAhQYvEZ1IklrVGRFIfK88LHIcg8XyTk8fPpk2+a1+b5K8WvzE9Lc1kw13fv3pOQE0I2knpK8LfzZT6eRxitaqk/VlPpOvi350fvcTvXhuKcHSv+iG7MGTvG+eKz/sZzfFM7y1M/2/zoz/hn7f3xIz/xyI+8px0nL47UxQU2TRT3brIkjR4nH0/aZv4M+n9UkOeV7EAVCXPNrB1y+YHTNO/9EyfmP0/mtcyDNdQyHVcCiFtTJbpBLEicY4OBEfwvtxMU4hlGJy7Fw0OXDtsvdYqKR0FU3+fbreWcxNfbqxm2pG6z1LSWbL1+epp+dMLBI2kdoGNMH4vz2DqGkIPlCFWw1sKDw3hWDefq1fW5d9YdniZ/F4OB7arSnsF2T3JADHk4UfaEfwvbzL6DSf/vhmxgrOendefLBTu7mtCqy8DNVksWocndYrhcWFTA6Rj8jY8DdBe0behw1KKOg1LM4z4I/iATsq3qyd5lWETg5C/nAbbnS2aB1h3C7a2b87gW0pWoOhhJxZijlYj66PFNkpBQqyYzW7MCO7UPN6+OZHpt8ZB516vZxM1wHPBkOBzHyq9QxwQp55VLlffw1s2oTPOI+8PXyUD2sueBGeEZEdDfuau0WRZTJbIY3gpo9Qsw4T4vgGL/n8LenFyVrNfeVDuqPn2gF4G6W3Y317WYNxPuQ/qb+lmeJExTF67Obib9y03ZJcXdJ1TRrzECP9lWx/smPDR3oM6WyYi0sLAYA4qQWsBc0CGM6OTINBPWmOtik82MkOBMqqxTtanaGSdZJ9nBUBJETIpcpcC1vDAOIgRLQP8J9PAi82WdW0LzvjDw6lj4g4c41SvNDuFtNijG+Q2oZeF/hWMwFSgj6VkGLoLmL3kuTBUnEpLdLeijDjB/3z8ZkdagCnYqyhqS5zxMdWSFx73J7NLyXlFQjq7wsoFQGLxXNn7QRAjj2XjMXvPCPI0VU3q3CzovsA7rM7b0d0axgS3oniJMYbdLsN9Y/j82dv2Qol0yzmkmb41Lb4Qt3rhawDfOELpf1srG2tC0iB7p+5g58qXM11bB7/X8ig1bRaTr/d2kWjgtzxZcY6rQaFfJpt9UvMzEXZAWTRIzZylmjZ8mkoLk4q3LsWxwIfCyoLsvHWCnbswOUeRe5x62B1baBZKYMl2JZ5ijan2NlVnfv6vXzixJbdThr0AQMFvdOlPNe2teiJcT8E7qZHaEY7w9cUpBvbtcQeRbK2mKi/1t+4Bg+nV+ZXJkZn0/iPcnNJCFiMyiDfblSBlTb78buaEGJ+ClFxaFqvpNSXsbPJfZTy1utc9ZXM/n74hy/uXYZ+bzy7Je5O//4us9+Thi7EgUlssd892sfypEY/5RxSaLu3Z6FSeM86njOoHp43PbV9IOGxsARycQJz3/pzIX5xnzQ6Pnexq6VvcvMW1d4aVg76IyR5+dGKaKIM+2gUukYYZErpsHqGRzTCZqTIrXGD/4vBC85ax5JFxxGfD34643hf86Y/YQ+qagHfpm624B+L9Ma9qv0PNEigW/g3QPaH/pgmjXwytZC/SVEIbnxJjAGDjgleQ5bib3r1yQCWeaT/L9oqB0cfpq0P23rEC9lkuDzrCu9zhC+08khQ+Oi0Zuy+7pvDVcc5LIOiop4/qiq9Zju7+Ld92tj60f6bkJGs+J9h+bG8shPxWkpqDQMVdsskRExfoPURoPbGoE3UzN2w1V1Ci9pa0wu+ASg863XR8L1k/RztRuH3ciOw0HtBDBezNfSWISV64/9QcP/SiGeevSrHkGELIFJSZ4nQohhDQypIFibI8aIDPQ40yhtoAYOzfeU0iFGWE2yDnp/liob/XTr77IV6PmwiH9ukIvt13Yf6/1v9hwXM7Zs9rLE9dHQxRrjSjE+hP6y7KT3xv4FJmYWj7qgB90AEAiKdH9oPFwPQkjRPLcsAyoTn5CEE+BT92Dcv++PY6bkZbgv8oSu+ZPqyS4/zeL0Euawm0G9i7WopJ+f3FkEvoCE9HYRSHiB5eYLozabcOcTfCCjBVsYP/g+8u1jihiP2RPVzxT+Q/pv4akefD+kfZjVk6p7wYXx0vQw+L2fGr8mIbxi/SE4vsJjfXiMaMBBP6gHz229TiKVsR2PoqjR6AEitOo+qJdGwhGCJ5w6WRJ7GJ5LUKkaHKYGctgr+3nulqRtUTyh5dUn0+11P5Tco9xkPH5mfB+/7MyWQURX15J31/n36BcTnyLn2nljoZpJp1wfb7/Tb+t1gTEsWg0s6kaHFxx57/uxfg8yF/bBmBtxW/p1neSNM940kD3FJFZeNwN4nUWzGYngJTIUJUqiP+QRc8hLAdEoK3kAWGQpJEa4dfJhFsoTiHwS1dE6sEsaVOd8t6ubK5kxBuN+raBXtKgmP9/2xrNZXifw7sAFPJiY5a6CCWdM+EJ6ukhOPwgZO87uCQoVFK8sJQ4Puj0rs8g1rYQctHvdZ3xS1lHL2gIY+eAf+cU61JUACRA279B9wE6rf+ZsLcVpSSFUgpDEwvLrDFY6usUKRTj4PwG2yNo6W+VeWa11d3sNC39JMu/MMFec5cMMOv29ExWM6KBiQbauaC2oRGjCprZZ+jmQLwJ1najN0QdhzpBcJ1t+1jofDL4v4w1J3pOtK+Xpk5Iw4YA2GvhJvNVe2wzzxs5/nZBK5uho6zwFgiSbDJy5P9mOTj8QCi3upNsvyqUVEmBcU5EjtjM+7XT8v3xWqbS+zA5JHnwPkmsAVzbEToQ/vrGU87kR1CYHvYqOIqCZZCoS1LwSNfDDghbIZojvOkFiEF24jGbQ8Xk9x4eqJBloixLDYjzo2ozhGl6B5Xn7WaSntjuUyYEu76u3uOYUvnCTlXVdlLkKdJBOe8pwwszT9DDj4+GPyBj/ghRQQ8x+19nViwTH/oWxZA1/R2gv/unFj//aeKfX/z/+5vJb/9x/BC20gvSxQHKzRRLzkN+M/Hrf4f/P/ujJogA9fSba7f/rf1A0VO5n3g0i9P/QDC5CxkR2V2UiAEAAQz7NXvld873qtVut1JzV3U3rnv3c14md165dy5V5GpSyZdLsufJSpVVk+SVKyqVq173OVXbDUECKIeKEFFEQEBUQFCo6giIAgooILALgh0eID/sivoO0WjIhoyGav0BZ5cxvfe5zDLkcH4VgjISygjrYl0rU8RYQxakrB2yOmV0yp6xIqawMCyd+UcTxizi3idVYF+fGoBaGaEB5TzVVnQvYgUgf1ZNjCMzYcuixuKYEwQkBUAAAEAEMFL9y01h53pwDs3m1ESfjYOfbw4NgviNAJwwWPHAE/8e8BSBIAgNGBNohMDgAwAlCHAMAaAJAlEcOHIBWA8BEgbsAbCSGSl+QICoBEA9Bk4eJCuAeAOoDeA1ArwekOeBIAZgCQPhBJ52QN0BHAdAFoPlDVQLkDQCwBYHrxpsSCBcgmAKAaRbMMiBwAgHUAtoVyAYB6AVA643EPHg1IJgEgeMGwBw4AbBYAgDSg5iGIDmQSgDAS0GoBkodzBIgGAOgewKtNmgHIKQGwEqHJhC4OACcBuDRA6uIrDwgIAIQXQKUDZgaAEQHAJRHagUQNgCgSYFtDE4YOAkB6AcA0cNyCEg8kBQBwFmB70TcG4gmAZQHABxDc4fsIwBgAUgPQH3FWCxYPgCoDMD3A0sOUDdgFgCABQGsw/snsB8BqAPAukV6MYgxIEAGQBsDNQ0yHRgOAbAGYI3GXQ0oKYDKA3AJwnWZbAowEAZAS4a2C6w2oMgCMFpBpUMSNRgqoOgA9x+H7Hf65P4c/7+pdyv8S1+GzReLe2MulSt1FhXJfvKK6KIDCvL7sh4p+vvop6GZfe7Ezllq1L1uxJva50WXgej/pZBkeN6Xa+K8mI1nTHKPHFVY+W5z2oVkf6W82C5tKanRejbdujfTTBVmFjhrpCI9hU49lbdRNSs5RshkqW2HSlQWlhnbKXFIPZG5prHUcMtNmk2pxgJDIgdylfFOW6XCcJiUPtK7+AoLv4+iQ7a6CUV+5kJbu881L0cTlqGwvMEIy00G5ikBkb2jV0IW1vHVlWmPQqKzALL3hppa+E8fIpSxifJ9yfiGteO3hWdMbrsCkVktc47z14ecdSFL7/Ja+yJrMcxn6UkhIlXJ4gYO6p7x6PBbFIkTcb4Jr7nGq5TPcsr01fseVQvM3gn6j4uhMUZHDIfaS+F1X0VKFSJch7UorP0TmW1Ty7wh7VfKTVLOQoHGY7LbjjUKDJ2JpIxQaSPkkfKehK9+ncF/mk4I+T2JmskNVnBtrOC55AtouUREAuCGccPnUMrtoUgWDqEuHLmh8SkRhNQhxbzGvxG4CAQYaqXI5bbWdcScSNEDreEbiLlpk4bmXMtkm4Hgq/iRymyXzdAJPrwLYTFDL8JdqerWCJq6ftTEepJITkLSqn9s0hBu6WPxIwuVc6MtYU8CD1nhJii5FbLkJbKRlhT0fy/QRohqHqglmA3l4BKegCpUe230G7T3YSrDiml0mKUXM5ZZU+73JkVZheRGFpKcdvEJLkfEhU1MYXImlGc5qGc3twrcn6MwvTGuYhNmPBKCamFq5b44O83BcW6JNVbI52QrFwov4/Hnec4b7cLed0IXghIOjz0HeWqVOyj5kg44rg3VRgK3QwgdX6/EvgC5VAmA/qpikGCzIaa7KgZLBPOSSg/xQ0f+qON0xuMg1QMIeG2UYijdBKcjSh2vfEDi4mUwyxkuKtD5xTJiRnQIVX6QkLPVPR01J8n8coZ0YlkCutiNC3rShN6xKVlMq3DYFOj49Ok1dgiHRmqxz8cMvmQrbNaKjApn5/OyRZso5Iowyon2osciwOTGQcMbcfaFLgPudBumnGdR7Ny+CJZ0hF/BmMRQb5yR9wYR2NjLHAc7jibYbWVtFNjCFUqF4kshjNWhYxLHRVVBrZ0H/b7HkH1SQ6S9QTZ+G2zFfLQic4FjYkuv+CWe1xLuZ1ie8qvB2FwcKHb4ydppAZjKzL8e1I7Nize7AxMllKEAkFDtLTdozMnhey+q+uyhd4VFl/zSwhWJSCBpLpMRj8LykUhFPsZDEtlBnOYQuptuknHJ6XWuQJrOA1FDrctHkp9lpk9i4N9GHB0wp7xKIwg+OjmBtOYH04i8cCdX1ZIBgMNHP6hEHyhPUN4hloJIBlAL4BhobnCdAbT5o0G3w2lGSYxsFf42ACuweCCh4bECycbfJF4G9gzkHJhrkKChrAOfhQ6MPRceMlAo2HcQs8GwfyCh4bUpb0Ovhccy6MF+Az6FQA5MFzwxkB6Ae/uq4OGB/yjsgNfh7sMvu+iDDQaqDwgdl/a4AudxIj/kG+BtejCg28GMAwGFzYwNHJIvzBvpXiDfnggPgB4bBjANn9lTfr4TzJl0b+DRhvlouIj46NjJOQ6dSipM/cctKGhU6aIKdV6SOo6maahFmEHKYfpcojE52NmTBoSjojyyahwxkA4Kjpm0lXZWylFcvMAjCgoPcpoqfEIR5aDUYyeJmopTNvQ5I4TePJ9NARjJ0aQ8OQzgVQKCtqrJqLDUiTGM66zOJwvxfrEZB6N3o+Hc68rTO+KxqYW5ftpuDmO7RObI7GYbONP41KWkWmN4kdRHR0c5quuhJZEcdz8WuSLPCRRHEVGI0ysYPUspJ6aTBKeW4//OZeTzVykrH2GOM49SXjcVsi15B5J/cTNKMus0r+cU91qidhppx8VZRAdGhRSJ1OWVV8IJbWUqRhQe+jXf4Qe44umDB9136y8phKe0SwhsyTCiSQUQPP+/jPWoCbYvVK5fXS2ND1Fhox4To7BdBjmY3YNFI4UyGaDHHlXTY7KywSf44Uua3bHZFTGMKoYt63VyUkKa7MjjFSO1S26VujCJZf0GZmDkjRhTXLBQ3B964Er80YiXBlP+pVLFrZWOTMz8gb7rHTIZEk0lKUwnctDYVPF3ObuqAwxZ34bUrxK3/CgF6DPjX0ULsyvt1QufXmYYS1x36Lz/Uxqr4J1nfQRpy00QSzEHo6C/g1wveF7pZPd/Orio4+bMIOGYpSbLfgRQoaNXCNjQjEn0bbPVPhwkYISo9AKHt5VD8MqLmPMCaI8EwdF1IwV/q1N+neYxoXUgReCuFHlb9yYVqj1hYaYnNXFfevRtBQLE/XepYv1EEoUwgKt+fu7jNpDQp3wk9ShnOass5RvP2WmUjS3xYh+DE5q+h1T0HICLBmpgBO02UinNC2ManA/3M+kVf3K4gQtBYaU5tFEPxYiSPkht6qMeOvj7EeFZKZYl608UalzyooN0xZy+OybWEZxiXNSlKHb3WmvCKCXl/cOKzbYzKRksm4oDqhglgvlRcorV+Djt9MaXQgKzaYhVo0zHLjdniDSyWKYUj+pEP/dsVSNg0xmEKHm/N72cVI5WKvnnnQhs2YriRR/giAvTF44wmpfWQiqcjtozWtvX9E8QZNRTvxIJh66rFIZlHSGO/qkpqoGN9o1hZlng0ZaxjHSY0Of5R1w2zJWOaShblsQnElYjZHGQWX3OStrreXMktn78Oq8MKkq33c9qnx9LmksK2vnTMUDT6IRidD7bFA2JeEVJrUvwjbqGxpTCb/v9TcKG+nwYTNIQGGTsREPA8PjDf64gdl/cLB62BZsg/xiE7FhJiSwKdiUbIw2TJsVsBps9dg+FNjYEsnY5Id5BXUKAPlYgYVC9WF/WLCR2JQWeiqYU5CgQFwhtcLZYcgmYSOwQQ9nC5hsFgoobPLDiI3PuIQRfiiw4dhvh/phfjhd6Gs1Puwu8F/IuaB8QZVC34WC/LaAg0GLDcJmtYBK4fkwYSOCXvP7JQULC/mH4mF8+B82bLoLFmyyCyWHieG4pvtHyeyrA2AFCVeUAvyF8gysFzz/i06FC76HTZvTwzQFKgtwGYgPOwtNGr4vTGWg0BCNIe6C0AUIDX3ZBo+gHh5t08P6cItHuuB7GGaI1wDERmMDY+A+PLphBPrgEa8M5IfoBeDDFsMMhi8292Gd4f5wPswvkGjo
*/