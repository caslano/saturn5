//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_SUITE_HPP
#define BOOST_BEAST_UNIT_TEST_SUITE_HPP

#include <boost/beast/_experimental/unit_test/runner.hpp>
#include <boost/throw_exception.hpp>
#include <ostream>
#include <sstream>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

template<class String>
std::string
make_reason(String const& reason,
    char const* file, int line)
{
    std::string s(reason);
    if(! s.empty())
        s.append(": ");
    char const* path = file + strlen(file);
    while(path != file)
    {
    #ifdef _MSC_VER
        if(path[-1] == '\\')
    #else
        if(path[-1] == '/')
    #endif
            break;
        --path;
    }
    s.append(path);
    s.append("(");
    s.append(std::to_string(line));
    s.append(")");
    return s;
}

} // detail

class thread;

enum abort_t
{
    no_abort_on_fail,
    abort_on_fail
};

/** A testsuite class.

    Derived classes execute a series of testcases, where each testcase is
    a series of pass/fail tests. To provide a unit test using this class,
    derive from it and use the BOOST_BEAST_DEFINE_UNIT_TEST macro in a
    translation unit.
*/
class suite
{
private:
    bool abort_ = false;
    bool aborted_ = false;
    runner* runner_ = nullptr;

    // This exception is thrown internally to stop the current suite
    // in the event of a failure, if the option to stop is set.
    struct abort_exception : public std::exception
    {
        char const*
        what() const noexcept override
        {
            return "test suite aborted";
        }
    };

    template<class CharT, class Traits, class Allocator>
    class log_buf
        : public std::basic_stringbuf<CharT, Traits, Allocator>
    {
        suite& suite_;

    public:
        explicit
        log_buf(suite& self)
            : suite_(self)
        {
        }

        ~log_buf()
        {
            sync();
        }

        int
        sync() override
        {
            auto const& s = this->str();
            if(s.size() > 0)
                suite_.runner_->log(s);
            this->str("");
            return 0;
        }
    };

    template<
        class CharT,
        class Traits = std::char_traits<CharT>,
        class Allocator = std::allocator<CharT>
    >
    class log_os : public std::basic_ostream<CharT, Traits>
    {
        log_buf<CharT, Traits, Allocator> buf_;

    public:
        explicit
        log_os(suite& self)
            : std::basic_ostream<CharT, Traits>(&buf_)
            , buf_(self)
        {
        }
    };

    class scoped_testcase;

    class testcase_t
    {
        suite& suite_;
        std::stringstream ss_;

    public:
        explicit
        testcase_t(suite& self)
            : suite_(self)
        {
        }

        /** Open a new testcase.

            A testcase is a series of evaluated test conditions. A test
            suite may have multiple test cases. A test is associated with
            the last opened testcase. When the test first runs, a default
            unnamed case is opened. Tests with only one case may omit the
            call to testcase.

            @param abort Determines if suite continues running after a failure.
        */
        void
        operator()(std::string const& name,
            abort_t abort = no_abort_on_fail);

        scoped_testcase
        operator()(abort_t abort);

        template<class T>
        scoped_testcase
        operator<<(T const& t);
    };

public:
    /** Logging output stream.

        Text sent to the log output stream will be forwarded to
        the output stream associated with the runner.
    */
    log_os<char> log;

    /** Memberspace for declaring test cases. */
    testcase_t testcase;

    /** Returns the "current" running suite.
        If no suite is running, nullptr is returned.
    */
    static
    suite*
    this_suite()
    {
        return *p_this_suite();
    }

    suite()
        : log(*this)
        , testcase(*this)
    {
    }

    virtual ~suite() = default;
    suite(suite const&) = delete;
    suite& operator=(suite const&) = delete;

    /** Invokes the test using the specified runner.

        Data members are set up here instead of the constructor as a
        convenience to writing the derived class to avoid repetition of
        forwarded constructor arguments to the base.
        Normally this is called by the framework for you.
    */
    template<class = void>
    void
    operator()(runner& r);

    /** Record a successful test condition. */
    template<class = void>
    void
    pass();

    /** Record a failure.

        @param reason Optional text added to the output on a failure.

        @param file The source code file where the test failed.

        @param line The source code line number where the test failed.
    */
    /** @{ */
    template<class String>
    void
    fail(String const& reason, char const* file, int line);

    template<class = void>
    void
    fail(std::string const& reason = "");
    /** @} */

    /** Evaluate a test condition.

        This function provides improved logging by incorporating the
        file name and line number into the reported output on failure,
        as well as additional text specified by the caller.

        @param shouldBeTrue The condition to test. The condition
        is evaluated in a boolean context.

        @param reason Optional added text to output on a failure.

        @param file The source code file where the test failed.

        @param line The source code line number where the test failed.

        @return `true` if the test condition indicates success.
    */
    /** @{ */
    template<class Condition>
    bool
    expect(Condition const& shouldBeTrue)
    {
        return expect(shouldBeTrue, "");
    }

    template<class Condition, class String>
    bool
    expect(Condition const& shouldBeTrue, String const& reason);

    template<class Condition>
    bool
    expect(Condition const& shouldBeTrue,
        char const* file, int line)
    {
        return expect(shouldBeTrue, "", file, line);
    }

    template<class Condition, class String>
    bool
    expect(Condition const& shouldBeTrue,
        String const& reason, char const* file, int line);
    /** @} */

    //
    // DEPRECATED
    //
    // Expect an exception from f()
    template<class F, class String>
    bool
    except(F&& f, String const& reason);
    template<class F>
    bool
    except(F&& f)
    {
        return except(f, "");
    }
    template<class E, class F, class String>
    bool
    except(F&& f, String const& reason);
    template<class E, class F>
    bool
    except(F&& f)
    {
        return except<E>(f, "");
    }
    template<class F, class String>
    bool
    unexcept(F&& f, String const& reason);
    template<class F>
    bool
    unexcept(F&& f)
    {
        return unexcept(f, "");
    }

    /** Return the argument associated with the runner. */
    std::string const&
    arg() const
    {
        return runner_->arg();
    }

    // DEPRECATED
    // @return `true` if the test condition indicates success(a false value)
    template<class Condition, class String>
    bool
    unexpected(Condition shouldBeFalse,
        String const& reason);

    template<class Condition>
    bool
    unexpected(Condition shouldBeFalse)
    {
        return unexpected(shouldBeFalse, "");
    }

private:
    friend class thread;

    static
    suite**
    p_this_suite()
    {
        static suite* pts = nullptr;
        return &pts;
    }

    /** Runs the suite. */
    virtual
    void
    run() = 0;

    void
    propagate_abort();

    template<class = void>
    void
    run(runner& r);
};

//------------------------------------------------------------------------------

// Helper for streaming testcase names
class suite::scoped_testcase
{
private:
    suite& suite_;
    std::stringstream& ss_;

public:
    scoped_testcase& operator=(scoped_testcase const&) = delete;

    ~scoped_testcase()
    {
        auto const& name = ss_.str();
        if(! name.empty())
            suite_.runner_->testcase(name);
    }

    scoped_testcase(suite& self, std::stringstream& ss)
        : suite_(self)
        , ss_(ss)
    {
        ss_.clear();
        ss_.str({});
    }

    template<class T>
    scoped_testcase(suite& self,
            std::stringstream& ss, T const& t)
        : suite_(self)
        , ss_(ss)
    {
        ss_.clear();
        ss_.str({});
        ss_ << t;
    }

    template<class T>
    scoped_testcase&
    operator<<(T const& t)
    {
        ss_ << t;
        return *this;
    }
};

//------------------------------------------------------------------------------

inline
void
suite::testcase_t::operator()(
    std::string const& name, abort_t abort)
{
    suite_.abort_ = abort == abort_on_fail;
    suite_.runner_->testcase(name);
}

inline
suite::scoped_testcase
suite::testcase_t::operator()(abort_t abort)
{
    suite_.abort_ = abort == abort_on_fail;
    return { suite_, ss_ };
}

template<class T>
inline
suite::scoped_testcase
suite::testcase_t::operator<<(T const& t)
{
    return { suite_, ss_, t };
}

//------------------------------------------------------------------------------

template<class>
void
suite::
operator()(runner& r)
{
    *p_this_suite() = this;
    try
    {
        run(r);
        *p_this_suite() = nullptr;
    }
    catch(...)
    {
        *p_this_suite() = nullptr;
        throw;
    }
}

template<class Condition, class String>
bool
suite::
expect(
    Condition const& shouldBeTrue, String const& reason)
{
    if(shouldBeTrue)
    {
        pass();
        return true;
    }
    fail(reason);
    return false;
}

template<class Condition, class String>
bool
suite::
expect(Condition const& shouldBeTrue,
    String const& reason, char const* file, int line)
{
    if(shouldBeTrue)
    {
        pass();
        return true;
    }
    fail(detail::make_reason(reason, file, line));
    return false;
}

// DEPRECATED

template<class F, class String>
bool
suite::
except(F&& f, String const& reason)
{
    try
    {
        f();
        fail(reason);
        return false;
    }
    catch(...)
    {
        pass();
    }
    return true;
}

template<class E, class F, class String>
bool
suite::
except(F&& f, String const& reason)
{
    try
    {
        f();
        fail(reason);
        return false;
    }
    catch(E const&)
    {
        pass();
    }
    return true;
}

template<class F, class String>
bool
suite::
unexcept(F&& f, String const& reason)
{
    try
    {
        f();
        pass();
        return true;
    }
    catch(...)
    {
        fail(reason);
    }
    return false;
}

template<class Condition, class String>
bool
suite::
unexpected(
    Condition shouldBeFalse, String const& reason)
{
    bool const b =
        static_cast<bool>(shouldBeFalse);
    if(! b)
        pass();
    else
        fail(reason);
    return ! b;
}

template<class>
void
suite::
pass()
{
    propagate_abort();
    runner_->pass();
}

// ::fail
template<class>
void
suite::
fail(std::string const& reason)
{
    propagate_abort();
    runner_->fail(reason);
    if(abort_)
    {
        aborted_ = true;
        BOOST_THROW_EXCEPTION(abort_exception());
    }
}

template<class String>
void
suite::
fail(String const& reason, char const* file, int line)
{
    fail(detail::make_reason(reason, file, line));
}

inline
void
suite::
propagate_abort()
{
    if(abort_ && aborted_)
        BOOST_THROW_EXCEPTION(abort_exception());
}

template<class>
void
suite::
run(runner& r)
{
    runner_ = &r;

    try
    {
        run();
    }
    catch(abort_exception const&)
    {
        // ends the suite
    }
    catch(std::exception const& e)
    {
        runner_->fail("unhandled exception: " +
            std::string(e.what()));
    }
    catch(...)
    {
        runner_->fail("unhandled exception");
    }
}

#ifndef BEAST_PASS
#define BEAST_PASS() ::boost::beast::unit_test::suite::this_suite()->pass()
#endif

#ifndef BEAST_FAIL
#define BEAST_FAIL() ::boost::beast::unit_test::suite::this_suite()->fail("", __FILE__, __LINE__)
#endif

#ifndef BEAST_EXPECT
/** Check a precondition.

    If the condition is false, the file and line number are reported.
*/
#define BEAST_EXPECT(cond) ::boost::beast::unit_test::suite::this_suite()->expect(cond, __FILE__, __LINE__)
#endif

#ifndef BEAST_EXPECTS
/** Check a precondition.

    If the condition is false, the file and line number are reported.
*/
#define BEAST_EXPECTS(cond, reason) ((cond) ? \
    (::boost::beast::unit_test::suite::this_suite()->pass(), true) : \
    (::boost::beast::unit_test::suite::this_suite()->fail((reason), __FILE__, __LINE__), false))
#endif

/** Ensure an exception is thrown
*/
#define BEAST_THROWS( EXPR, EXCEP ) \
    try { \
        EXPR; \
        BEAST_FAIL(); \
    } \
    catch(EXCEP const&) { \
        BEAST_PASS(); \
    } \
    catch(...) { \
        BEAST_FAIL(); \
    }

} // unit_test
} // beast
} // boost

//------------------------------------------------------------------------------

// detail:
// This inserts the suite with the given manual flag
#define BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,manual) \
    static ::boost::beast::unit_test::detail::insert_suite <Class##_test>   \
        Library ## Module ## Class ## _test_instance(             \
            #Class, #Module, #Library, manual)

//------------------------------------------------------------------------------

// Preprocessor directives for controlling unit test definitions.

// If this is already defined, don't redefine it. This allows
// programs to provide custom behavior for testsuite definitions
//
#ifndef BEAST_DEFINE_TESTSUITE

/** Enables insertion of test suites into the global container.
    The default is to insert all test suite definitions into the global
    container. If BEAST_DEFINE_TESTSUITE is user defined, this macro
    has no effect.
*/
#ifndef BEAST_NO_UNIT_TEST_INLINE
#define BEAST_NO_UNIT_TEST_INLINE 0
#endif

/** Define a unit test suite.

    Library   Identifies the library.
    Module    Identifies the module.
    Class     The type representing the class being tested.

    The declaration for the class implementing the test should be the same
    as Class ## _test. For example, if Class is aged_ordered_container, the
    test class must be declared as:

    @code

    struct aged_ordered_container_test : beast::unit_test::suite
    {
        //...
    };

    @endcode

    The macro invocation must appear in the same namespace as the test class.
*/

#if BEAST_NO_UNIT_TEST_INLINE
#define BEAST_DEFINE_TESTSUITE(Class,Module,Library)

#else
#include <boost/beast/_experimental/unit_test/global_suites.hpp>
#define BEAST_DEFINE_TESTSUITE(Library,Module,Class) \
        BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,false)
#define BEAST_DEFINE_TESTSUITE_MANUAL(Library,Module,Class) \
        BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,true)

#endif

#endif

//------------------------------------------------------------------------------

#endif

/* suite.hpp
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
*/