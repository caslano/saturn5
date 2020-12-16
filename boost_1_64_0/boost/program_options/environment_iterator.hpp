// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14
#define BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14

#include "eof_iterator.hpp"

#include <utility>
#include <string>
#include <cassert>

namespace boost {

    class environment_iterator 
        : public eof_iterator<environment_iterator, 
                              std::pair<std::string, std::string> >
    {
    public:
        environment_iterator(char** environment)
        : m_environment(environment)
        {
            get();
        }
        
        environment_iterator()
        {
            found_eof();
        }
        
        void get()
        {
            if (*m_environment == 0)
                found_eof();
            else {
                std::string s(*m_environment);
                std::string::size_type n = s.find('=');
                assert(n != s.npos);
                value().first = s.substr(0, n);
                value().second = s.substr(n+1);
                
                ++m_environment;
            }
        }
        
    private:
        char** m_environment;
    };
}
#endif

/* environment_iterator.hpp
hq2dx9J2Nt6K71j4mel4KYZT7ElMLbW5S8i9ldzRfIg7ES8n0gD7JiDaaWB+28fNv/PrPo4++jIMSspMu/4nc+8Q0/W66UdyD4/gYk6NbqtUyZbdsAtbe7Fn8n4259YVtGYc79Yeh6WM15Ddm4tgO1oznbONF7s/itmvy5R69R6Zj2XDzMx4PDvubD7bty3nWGGud/VF8E7Yb5N9VD6ancgU0qmiLlvyu4sO1O8NlLG7dYuMyavIfSrcjs2gaFpSrHx5QX1MFr2P4r2gx+vzVbkyXqwk97UQl3PMak0rlgvVWSZmJI7WMG07cE4frutF/fFCyvsZMr8KMTE+p4rW6KW/jhF+245e7A1z9fixRDqeUa/vMud9hPzZcLmP6a5jpIy328mLnQ3rmyoW88pzTsnju8l8OsxMVIpYxoA9VYjnqr2KLl/a1k47e7GfiOYjxE3Dopt+rVXygGlYmY1OAztzJ+xFu3ixbwzp71vmZDMlR/YvsqdDelNfZ+P2+rt6sZ8JjZ0LYUe/iuwHA/ntzjYi7ewXcmdCed0eK1UKhXyx7HjOUN6N+4qhvqwNnakZOpXHLeF+S+6aXBQ3VkqUdfWVfqWwuxd7RVhfn0UoJlYaZbuU6P4107CoJg3JeA5TpWwprsqVupbew4u9aTQ3XsEWJHYFL9eu69K+15B/fw0/ni3kvFmTdp7LmD2yJ036/nY2Vky5mqN8SN5zfl0xZqJFxy5JXQ5jQtWqgHVuPKvKlzrW18y9Zn9fmszDnJFLYilyibbewn2D3D387dpW61g8qbzHLdzOveg7N8w1Bu6xbFx5vSfc58ndqYabysVH9e2QUp/33duLvZu/fiXKxawyT/R8kLzPcgEezJBUVLlcZe67aB8v9qe+esy9IXX7o+TtNJkdASbcZSjPtSVv15L3TNbPS6cSl7hZxwi3QMeHOwTqEOZaJU9bV9yvyb3IV5fsPqOpxLpcO/7tx/flfPpi6IHCxjzhP7jghP81+a21/GSqlHDGl3p9Tgv93vvrtdl31F1HyFxrlryvLG/ubFe1W26f28hXb8uS58v392L/EJWGAvLbDMfZ/LgyX+r6h+T/OFGHr2zftuP/AV7sbyP0drE/Z8d/cgcjuGY9ldGd38ncsutAnkeK5pp1hfb+nOj8Mtk/R5SxizmmtK/Og7zY3X6dsVY157+M7RP1ayzvZD9U0rCKaWiOSkOhdAnKG+YKLCpiafW6LmnoPphzhGwoDaEzeNWM0C6LDqn3TMPaUBpcnwOUPOjlYw4fhvihs4BO6kKr5AHT8EMoDS7PI9r5/yH02ZQLsl2d0bP1n9yXJyK4WPJgaKuqb3YCtPP9eOnrW73YnVG6Y3+P+ntnBe1ESzctx8h4x7RckY9Oi91bdZQOaY8jh3qx22ryxO0er13/k7+kHh+TvVRuvJxW5kuduKiNZ+uzdfi0IxcuS9qS0K6f0i/MMi0n5eqlZTQWL+rOeZdIPrTT7hOqjwtxnlTSsIZpOGciMg3YTcD46Lg9JDu82C9G5cOllYzvVK8qX/qFb8nfJYqPeQLnK87qoqSjfBjPcWej08F24Swd0ia+Zzo+DOWHy/O+J4l943DeGYhi5/Jlc/BmomrUkRZis0M1PdJXbX4EY0emx5rlS7AeTlZnUjgvii5DN2+kftzNtFw/MW9aaKxGMpTLSNrrdkv4NltUOqqzekf9heTDg+QvjyqTcZxjLWIy5/A8nKRj3yN59jGqvSZTY/FKlvM7N3Nb6cOfYDqa/0I6khndPWFpJ4cfxfdkcvXTYM76xjzfnLFsSt12KGlZxbR0zJcfiTIMK2af2mnZdB/NM1e1aVmwNLzNNGycj0pDPn9JJsU=
*/