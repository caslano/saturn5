
#ifndef BOOST_CONTRACT_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/static_local_var.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>
#include <boost/config.hpp>

namespace boost { namespace contract { namespace detail {

#ifdef BOOST_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4275) // Base w/o DLL spec (noncopyable).
    #pragma warning(disable: 4251) // Member w/o DLL spec (mutex_ type).
#endif

// RAII facility to disable assertions while checking other assertions.
class BOOST_CONTRACT_DETAIL_DECLSPEC checking :
    private boost::noncopyable // Non-copyable resource (might use mutex, etc.).
{
public:
    explicit checking() {
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            init_locked();
        #else
            init_unlocked();
        #endif
    }

    ~checking() {
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            done_locked();
        #else
            done_unlocked();
        #endif
    }
    
    static bool already() {
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            return already_locked();
        #else
            return already_unlocked();
        #endif
    }

private:
    void init_unlocked();
    void init_locked();

    void done_unlocked();
    void done_locked();

    static bool already_unlocked();
    static bool already_locked();

    struct mutex_tag;
    typedef static_local_var<mutex_tag, boost::mutex> mutex;

    struct checking_tag;
    typedef static_local_var_init<checking_tag, bool, bool, false> flag;
};

#ifdef BOOST_MSVC
    #pragma warning(pop)
#endif

} } } // namespace

#ifdef BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/detail/checking.hpp>
#endif

#endif // #include guard


/* checking.hpp
cA8NwjXxg6YI7lsNroPvFd1B/zNugeBOrcRvT9r/wecsiqR/N3nZeFWqq4gf5Z/5ektlrq6aLvUdrrypPmSo0mHdyj988w/pzKzMvQ/ZUeB/+5sLaY3nPYvHgn+f7kj+e5Ona/ZRlQ73wGs2+i/vJNko7cgspse07y3x66kT2rOJds0B7YEt/bHEwDAZFCGO0L18+RK8u5cvc6w0P3cvOLcyV+f9aaov17eLXFWOj03NyrBQ91IYa0T6owz7X8q9UeK/ybDBvBlwrJQ5DusyZWq0HMYTkXILRyin8U1suUVSbvEI5cpGKLdUypVLuT+BbYk2/XyCT/aGoltCZLYP+nmP++fsE1HAKZHYpJou9ZL96VRvfIvY5e+gvDIvQtrKTy+g9CKKQ0TGGZ13T68/MxrJ3EE7nmBVAjPXZRi+hMeOwPvIGIsm2MWo5SsI3qzw8EAsTDZvk/gQK0H3dfBb56GBeHxjethsAhCCu4HlOW9lx3P4TrFOjvBdROX1387+lje09S5CFfBQ5q11NWU/dkr9++Ue+E5Q3amhhpbOUHNtVzOTCAJk9Opy6fflOXu53ljCw7ZQOpS1wU+gMgX+PTj+XqyxMldU4j5ChOaKRt31Sm2RzZc3wIPblByg/cNQVMtqejQ5AH2fRazYAjJyeFdlxj7jv9Vuq5V8tT3qRKfU0P8Oq17mT0PlKD6Gg5SFo9dk6l1FabRlmqXeFsGbP8p4LDvcv5Pm9r518h3hZFz7/fHvP+ieTmUlZrJVXvPBTpF7hrD3Tab7+mJbXd1NUtdqqGvym+qfcQV50+G8sZFNh8hmonxTebfIplPwAsfJm5jzHDNHaK5HX4DoPJDBxtiwn+5hvelT4f7QuDSSp/tm/QZT4n+D4W8Sy+Uu+xqQXynyHcAwyqwJxvFaI7NTRWarZByfJjJ7j+LR38fMtraR/1YR2lFnSLlQJfqQ+LsG4z5pziuFBX+9wVdci98r+NEA/JuO3x9/g+D3o10n+BPtNxDB3Yi0AdfSHhT8of1p83qOfvBhwd0kuPwmt4ElR9MZvB7InctQd2djo3a2zc+OzTT03Yny9yPj/XHq+7/dqOKxxm2bzN/3eJzK9740KaF00oVbcHmO3xJaxwbEh/Rb/t7HUXXBNxlP9dO6TJQ573Rez3Pjh69z67jk6dmhSGbtzr0/28drNoVwoiWLIXTvXOl2SH4iujkeCacyvr4YwdYyLeJV2jdAeesE3+W6vDjl9XObXVaW7rDgyddNzk9Q/lbVVa6IyCBF+Ts0n0XzcobOeV7EebzSw7B2XujWfLp/p+mLOHYFyFlkfwnxEI4NcXoz0drppdiu0nJXeRS70R0W04NhUMc1fqwjcgEOp/oh/3o/39P+vtmje4UJWmhC0u+Sf7vkm77gOXC3wFhkQPs+zA8lI/rdOE2wBxXmnLbJ+JDIiOfJwzR+HIjrEB/448YHvoXav8ujdR7a/5K3nsqFUn68+miv3q2eQxNqK+jH1339mFGioCIxl+fMsSPE/C9y65SMCb51q2fixMfYLx5GXQOneX4aYmimE8PkkgZ5zfK4x+HeJfeWpDk+VTrVTx/HN0tsTDkjWGbOCPaUufnVH0/SgFSeqjidG++/xhuORhPSJs7ju76DdCmWcXj/x2kOuanf7mkexYYx1so6ShMCr6HuGtJZIOt+1lHykSfUUdtZuxqUlAHIujQ22zUb0SQQovc2RMdVylp8Pts+68n+yI7h7ZVivyY9+A7jNpFZ//cHRrBb9zdMxmR/c9vb606iGBZcPAiQsTt3VI4pXh4XbW1vP7mnI0vTADI0zxaaF+e8Y+AHxnPpD7FMyEYUmZxT6ceC9fWCmDyg80s=
*/