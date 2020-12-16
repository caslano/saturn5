
#ifndef BOOST_CONTRACT_DETAIL_AUTO_PTR_HPP_
#define BOOST_CONTRACT_DETAIL_AUTO_PTR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/operator_safe_bool.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/config.hpp>

namespace boost { namespace contract { namespace detail {

// Using this instead of std::auto_ptr because std::auto_ptr will be removed in
// C++17 (this library always uses release() to avoid ownership issues).
template<typename T>
class auto_ptr { // Copyable (using default copy operations).
public:
    explicit auto_ptr(T* ptr = 0) : ptr_(ptr) {}

    ~auto_ptr() BOOST_NOEXCEPT_IF(false) { delete ptr_; }

    T* release() {
        T* ptr = ptr_;
        ptr_ = 0;
        return ptr;
    }

    T& operator*() {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }
    
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }

    T* operator->() { return ptr_; }
    T const* operator->() const { return ptr_; }

    BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(auto_ptr<T>, !!ptr_)

private:
    T* ptr_;
};

} } } // namespace

#endif // #include guard


/* auto_ptr.hpp
ZQ31chrgWm/wHmn0ddbVXWTqnia0p0ndxabuYoBbeT0i8qL/GXcGlNW0wm1Z13fY50diWU4DHONYmbhRs82YIDiPiTnljM9jHfHnGXwH529lgr/P4B9j8PcJfpng7zb4xxr83YJ/nODvMvjvNPi7BH9hOcZTYDyAj/cWKVy+/1n4EqnPjRmsr9zU5+D8HcvUR3gAp9jSpj4Lr5b6ppn6TjD1TZP6Vpj6CA/g9M6Zqc/Ca6S+R4w860x9Ds7fsEx943F8Eb1GU5+FrwL4jQFxwlp8HVTwO/DtnCyy0HKtlLblVku5f0G5dlOuI6Dcu6Xcc1Cuy5TrDijXI+WehXKnmHJrA8qdauTHuhLjKxv5WfjpUq/TfVpvyNS7LqDesKnXjTeER0y9Fh6Veoug3g2m3v6AemOm3mmG7kZTr4UPSr1/ADnHTb3DAfVuknJ/hHJJUy4VUC5t+H3UyH+L4dfCtyn/oPdHX2PoCUdeZCAt69v7Db/bKa3nzWrk7usHZP5+UHDxnsq22bAWSOx/jMX0jgK43ylpfE+iyMQF+0g5xKIWeqovLpjOPmrmEf2/51FavnkzjPIDzxt/XPGAltJDvPMpjfKwb359ysDTXi78QsqzPFvf+2cMjRlmjFxk4PY88cXl8v3d1JESfDyncUlAu3dQnm33pcC3g+2QsYDfsr5k+LL3wb8cwJf+LF87Da2HbdwSA7dnW68oN2+t8DlZeBPH0PuGmXf49jR/ayA43qm/AmVO6VNMjJ0eebvNjrNvg427TmgWCo3roA60F9spjXZrDaSFZ9bT7TZ2ifYZw4NjLtwIOKRzA99RvlnrYRyB41vnAHf7pCvNvL3V6KTrTJ1B92RvMzhB7ynfYei+Dcay0A18z/mnahOUSDmwuTBdO1X5NefCjTzsGvlLA681/XKPgdv5fa+B2/t691HenJxvRXSkUf16BbLnh/u495ejP0m28IPhzPYCcniHgfPgEdO2B2VdewHWtYfMXuT3pl8eLh/hjOEYeHF1PQJr/h/RLtU1UmWMb9aDDH8vYwHXrT+LfnDywjdBiT6nL/Ry9UW3GQNPoR4v9t9mnSnvs7r/OSZKOeoEB4exDnf1nyW8A3yXb1zTEVptXZmcJ2v1cyIXrg/W6kL5oQ56XtbsvxpZbpf5b8/ivyj4fxP8++UemL+OO1dCNOE8CTIGWVdP1nw6YYRnZAs0f5B9L7x+lrCvJenS/HZ5qe+fiUWTXsZnU5Y5h8SwDM3d5a7vBnN8TlUBfqiaAD9Us/ihNC/NPr2Iu1xFtxGjkZjz9IR6YxtiqRycbrgb5tbBteKXDEXWe/otaF02j696afkXCL+ffZYEgTtdw5oHdxFfItytWZ+TK5DB3wH5WohgrC/O88hNkY4mtT/IpqXx7Iw7clzp+WWav5cYf3+x88OBrth5ABsR49zsM3riFTNfroD5uDvAZvm7+nMC/BPbjU9hL/qJDOxfsJ9lXNj/YXq71HPzEWCDYixVqfelADtnXAXiBMX/pT6qyLSX/bA2ztfECj9NMG2v4nN/Wb072dT5QgBfh0CdhMM6B/fah0mdKZUj2BuaxvIuH/fOBRVZfVYje3P3S6NuJf1SWJF7HvNw1qXq06HYNZQp9fC3Ivuu9XRoh8QsVp8Nw0sQTnmOLpafKe180pxPerUku44cWZG7Zh1lZHO01sEwOK8h68fsCtm3w9o019CcZ2i+HWjOE5p4p/AYgDuZ23X/HQZu47kdZ+DWLnmngVu75HiA7w6ALzblHQ7Clxq4vWtQYeC235fpGOc5IHGNzLnsasJR+XYbO+2ECvAVgc/T0cH0owBXWsOGVo3Q+n25pIH3RwLaVg+8E/1AO7o=
*/