//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_META_KERNEL_HPP
#define BOOST_COMPUTE_DETAIL_META_KERNEL_HPP

#include <set>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <utility>

#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/kernel.hpp>
#include <boost/compute/closure.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/type_traits.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/image/image2d.hpp>
#include <boost/compute/image/image_sampler.hpp>
#include <boost/compute/memory_object.hpp>
#include <boost/compute/memory/svm_ptr.hpp>
#include <boost/compute/detail/device_ptr.hpp>
#include <boost/compute/detail/sha1.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class meta_kernel_variable
{
public:
    typedef T result_type;

    meta_kernel_variable(const std::string &name)
        : m_name(name)
    {
    }

    meta_kernel_variable(const meta_kernel_variable &other)
        : m_name(other.m_name)
    {
    }

    meta_kernel_variable& operator=(const meta_kernel_variable &other)
    {
        if(this != &other){
            m_name = other.m_name;
        }

        return *this;
    }

    ~meta_kernel_variable()
    {
    }

    std::string name() const
    {
        return m_name;
    }

private:
    std::string m_name;
};

template<class T>
class meta_kernel_literal
{
public:
    typedef T result_type;

    meta_kernel_literal(const T &value)
        : m_value(value)
    {
    }

    meta_kernel_literal(const meta_kernel_literal &other)
        : m_value(other.m_value)
    {
    }

    meta_kernel_literal& operator=(const meta_kernel_literal &other)
    {
        if(this != &other){
            m_value = other.m_value;
        }

        return *this;
    }

    ~meta_kernel_literal()
    {
    }

    const T& value() const
    {
        return m_value;
    }

private:
    T m_value;
};

struct meta_kernel_stored_arg
{
    meta_kernel_stored_arg()
        : m_size(0),
          m_value(0)
    {
    }

    meta_kernel_stored_arg(const meta_kernel_stored_arg &other)
        : m_size(0),
          m_value(0)
    {
        set_value(other.m_size, other.m_value);
    }

    meta_kernel_stored_arg& operator=(const meta_kernel_stored_arg &other)
    {
        if(this != &other){
            set_value(other.m_size, other.m_value);
        }

        return *this;
    }

    template<class T>
    meta_kernel_stored_arg(const T &value)
        : m_size(0),
          m_value(0)
    {
        set_value(value);
    }

    ~meta_kernel_stored_arg()
    {
        if(m_value){
            std::free(m_value);
        }
    }

    void set_value(size_t size, const void *value)
    {
        if(m_value){
            std::free(m_value);
        }

        m_size = size;

        if(value){
            m_value = std::malloc(size);
            std::memcpy(m_value, value, size);
        }
        else {
            m_value = 0;
        }
    }

    template<class T>
    void set_value(const T &value)
    {
        set_value(sizeof(T), boost::addressof(value));
    }

    size_t m_size;
    void *m_value;
};

struct meta_kernel_buffer_info
{
    meta_kernel_buffer_info(const buffer &buffer,
                            const std::string &id,
                            memory_object::address_space addr_space,
                            size_t i)
      : m_mem(buffer.get()),
        identifier(id),
        address_space(addr_space),
        index(i)
    {
    }

    cl_mem m_mem;
    std::string identifier;
    memory_object::address_space address_space;
    size_t index;
};

struct meta_kernel_svm_info
{
    template <class T>
    meta_kernel_svm_info(const svm_ptr<T> ptr,
                         const std::string &id,
                         memory_object::address_space addr_space,
                         size_t i)
      : ptr(ptr.get()),
        identifier(id),
        address_space(addr_space),
        index(i)
    {

    }

    void* ptr;
    std::string identifier;
    memory_object::address_space address_space;
    size_t index;
};


class meta_kernel;

template<class Type>
struct inject_type_impl
{
    void operator()(meta_kernel &)
    {
        // default implementation does nothing
    }
};

#define BOOST_COMPUTE_META_KERNEL_DECLARE_SCALAR_TYPE_STREAM_OPERATOR(type) \
    meta_kernel& operator<<(const type &x) \
    { \
        m_source << x; \
        return *this; \
    }

#define BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(type) \
    meta_kernel& operator<<(const type &x) \
    { \
        m_source << "(" << type_name<type>() << ")"; \
        m_source << "("; \
        for(size_t i = 0; i < vector_size<type>::value; i++){ \
            *this << lit(x[i]); \
            \
            if(i != vector_size<type>::value - 1){ \
                m_source << ","; \
            } \
        } \
        m_source << ")"; \
        return *this; \
    }

#define BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(type) \
    BOOST_COMPUTE_META_KERNEL_DECLARE_SCALAR_TYPE_STREAM_OPERATOR(BOOST_PP_CAT(type, _)) \
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(BOOST_PP_CAT(BOOST_PP_CAT(type, 2), _)) \
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(BOOST_PP_CAT(BOOST_PP_CAT(type, 4), _)) \
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(BOOST_PP_CAT(BOOST_PP_CAT(type, 8), _)) \
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(BOOST_PP_CAT(BOOST_PP_CAT(type, 16), _))

class meta_kernel
{
public:
    template<class T>
    class argument
    {
    public:
        argument(const std::string &name, size_t index)
            : m_name(name),
              m_index(index)
        {
        }

        const std::string &name() const
        {
            return m_name;
        }

        size_t index() const
        {
            return m_index;
        }

    private:
        std::string m_name;
        size_t m_index;
    };

    explicit meta_kernel(const std::string &name)
        : m_name(name)
    {
    }

    meta_kernel(const meta_kernel &other)
    {
        m_source.str(other.m_source.str());
        m_options = other.m_options;
    }

    meta_kernel& operator=(const meta_kernel &other)
    {
        if(this != &other){
            m_source.str(other.m_source.str());
            m_options = other.m_options;
        }

        return *this;
    }

    ~meta_kernel()
    {
    }

    std::string name() const
    {
        return m_name;
    }

    std::string source() const
    {
        std::stringstream stream;

        // add pragmas
        if(!m_pragmas.empty()){
            stream << m_pragmas << "\n";
        }

        // add macros
        stream << "#define boost_pair_type(t1, t2) _pair_ ## t1 ## _ ## t2 ## _t\n";
        stream << "#define boost_pair_get(x, n) (n == 0 ? x.first ## x.second)\n";
        stream << "#define boost_make_pair(t1, x, t2, y) (boost_pair_type(t1, t2)) { x, y }\n";
        stream << "#define boost_tuple_get(x, n) (x.v ## n)\n";

        // add type declaration source
        stream << m_type_declaration_source.str() << "\n";

        // add external function source
        stream << m_external_function_source.str() << "\n";

        // add kernel source
        stream << "__kernel void " << m_name
               << "(" << boost::join(m_args, ", ") << ")\n"
               << "{\n" << m_source.str() << "\n}\n";

        return stream.str();
    }

    kernel compile(const context &context, const std::string &options = std::string())
    {
        // generate the program source
        std::string source = this->source();

        // generate cache key
        std::string cache_key = "__boost_meta_kernel_" +
            static_cast<std::string>(detail::sha1(source));

        // load program cache
        boost::shared_ptr<program_cache> cache =
            program_cache::get_global_cache(context);

        std::string compile_options = m_options + options;

        // load (or build) program from cache
        ::boost::compute::program program =
            cache->get_or_build(cache_key, compile_options, source, context);

        // create kernel
        ::boost::compute::kernel kernel = program.create_kernel(name());

        // bind stored args
        for(size_t i = 0; i < m_stored_args.size(); i++){
            const detail::meta_kernel_stored_arg &arg = m_stored_args[i];

            if(arg.m_size != 0){
                kernel.set_arg(i, arg.m_size, arg.m_value);
            }
        }

        // bind buffer args
        for(size_t i = 0; i < m_stored_buffers.size(); i++){
            const detail::meta_kernel_buffer_info &bi = m_stored_buffers[i];

            kernel.set_arg(bi.index, bi.m_mem);
        }

        // bind svm args
        for(size_t i = 0; i < m_stored_svm_ptrs.size(); i++){
            const detail::meta_kernel_svm_info &spi = m_stored_svm_ptrs[i];

            kernel.set_arg_svm_ptr(spi.index, spi.ptr);
        }

        return kernel;
    }

    template<class T>
    size_t add_arg(const std::string &name)
    {
        std::stringstream stream;
        stream << type<T>() << " " << name;

        // add argument to list
        m_args.push_back(stream.str());

        // return index
        return m_args.size() - 1;
    }

    template<class T>
    size_t add_arg(memory_object::address_space address_space,
                   const std::string &name)
    {
        return add_arg_with_qualifiers<T>(address_space_prefix(address_space), name);
    }

    template<class T>
    void set_arg(size_t index, const T &value)
    {
        if(index >= m_stored_args.size()){
            m_stored_args.resize(index + 1);
        }

        m_stored_args[index] = detail::meta_kernel_stored_arg(value);
    }

    void set_arg(size_t index, const memory_object &mem)
    {
        set_arg<cl_mem>(index, mem.get());
    }

    void set_arg(size_t index, const image_sampler &sampler)
    {
        set_arg<cl_sampler>(index, cl_sampler(sampler));
    }

    template<class T>
    size_t add_set_arg(const std::string &name, const T &value)
    {
        size_t index = add_arg<T>(name);
        set_arg<T>(index, value);
        return index;
    }

    void add_extension_pragma(const std::string &extension,
                              const std::string &value = "enable")
    {
        m_pragmas += "#pragma OPENCL EXTENSION " + extension + " : " + value + "\n";
    }

    void add_extension_pragma(const std::string &extension,
                              const std::string &value) const
    {
        return const_cast<meta_kernel *>(this)->add_extension_pragma(extension, value);
    }

    template<class T>
    std::string type() const
    {
        std::stringstream stream;

        // const qualifier
        if(boost::is_const<T>::value){
            stream << "const ";
        }

        // volatile qualifier
        if(boost::is_volatile<T>::value){
            stream << "volatile ";
        }

        // type
        typedef
            typename boost::remove_cv<
                typename boost::remove_pointer<T>::type
            >::type Type;
        stream << type_name<Type>();

        // pointer
        if(boost::is_pointer<T>::value){
            stream << "*";
        }

        // inject type pragmas and/or definitions
        inject_type<Type>();

        return stream.str();
    }

    template<class T>
    std::string decl(const std::string &name) const
    {
        return type<T>() + " " + name;
    }

    template<class T, class Expr>
    std::string decl(const std::string &name, const Expr &init) const
    {
        meta_kernel tmp((std::string()));
        tmp << tmp.decl<T>(name) << " = " << init;
        return tmp.m_source.str();
    }

    template<class T>
    detail::meta_kernel_variable<T> var(const std::string &name) const
    {
        type<T>();

        return make_var<T>(name);
    }

    template<class T>
    detail::meta_kernel_literal<T> lit(const T &value) const
    {
        type<T>();

        return detail::meta_kernel_literal<T>(value);
    }

    template<class T>
    detail::meta_kernel_variable<T> expr(const std::string &expr) const
    {
        type<T>();

        return detail::meta_kernel_variable<T>(expr);
    }

    // define stream operators for scalar and vector types
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(char)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(uchar)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(short)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(ushort)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(int)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(uint)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(long)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(ulong)
    BOOST_COMPUTE_META_KERNEL_DECLARE_TYPE_STREAM_OPERATORS(double)

    // define stream operators for float scalar and vector types
    meta_kernel& operator<<(const float &x)
    {
        m_source << std::showpoint << x << 'f';
        return *this;
    }

    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(float2_)
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(float4_)
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(float8_)
    BOOST_COMPUTE_META_KERNEL_DECLARE_VECTOR_TYPE_STREAM_OPERATOR(float16_)

    // define stream operators for variable types
    template<class T>
    meta_kernel& operator<<(const meta_kernel_variable<T> &variable)
    {
        return *this << variable.name();
    }

    // define stream operators for literal types
    template<class T>
    meta_kernel& operator<<(const meta_kernel_literal<T> &literal)
    {
        return *this << literal.value();
    }

    meta_kernel& operator<<(const meta_kernel_literal<bool> &literal)
    {
        return *this << (literal.value() ? "true" : "false");
    }

    meta_kernel& operator<<(const meta_kernel_literal<char> &literal)
    {
        const char c = literal.value();

        switch(c){
        // control characters
        case '\0':
            return *this << "'\\0'";
        case '\a':
            return *this << "'\\a'";
        case '\b':
            return *this << "'\\b'";
        case '\t':
            return *this << "'\\t'";
        case '\n':
            return *this << "'\\n'";
        case '\v':
            return *this << "'\\v'";
        case '\f':
            return *this << "'\\f'";
        case '\r':
            return *this << "'\\r'";

        // characters which need escaping
        case '\"':
        case '\'':
        case '\?':
        case '\\':
            return *this << "'\\" << c << "'";

        // all other characters
        default:
            return *this << "'" << c << "'";
        }
    }

    meta_kernel& operator<<(const meta_kernel_literal<signed char> &literal)
    {
        return *this << lit<char>(literal.value());
    }

    meta_kernel& operator<<(const meta_kernel_literal<unsigned char> &literal)
    {
        return *this << uint_(literal.value());
    }

    // define stream operators for strings
    meta_kernel& operator<<(char ch)
    {
        m_source << ch;
        return *this;
    }

    meta_kernel& operator<<(const char *string)
    {
        m_source << string;
        return *this;
    }

    meta_kernel& operator<<(const std::string &string)
    {
        m_source << string;
        return *this;
    }

    template<class T>
    static detail::meta_kernel_variable<T> make_var(const std::string &name)
    {
        return detail::meta_kernel_variable<T>(name);
    }

    template<class T>
    static detail::meta_kernel_literal<T> make_lit(const T &value)
    {
        return detail::meta_kernel_literal<T>(value);
    }

    template<class T>
    static detail::meta_kernel_variable<T> make_expr(const std::string &expr)
    {
        return detail::meta_kernel_variable<T>(expr);
    }

    event exec(command_queue &queue)
    {
        return exec_1d(queue, 0, 1);
    }

    event exec_1d(command_queue &queue,
                  size_t global_work_offset,
                  size_t global_work_size,
                  const wait_list &events = wait_list())
    {
        const context &context = queue.get_context();

        ::boost::compute::kernel kernel = compile(context);

        return queue.enqueue_1d_range_kernel(
                   kernel,
                   global_work_offset,
                   global_work_size,
                   0,
                   events
               );
    }

    event exec_1d(command_queue &queue,
                 size_t global_work_offset,
                 size_t global_work_size,
                 size_t local_work_size,
                 const wait_list &events = wait_list())
    {
        const context &context = queue.get_context();

        ::boost::compute::kernel kernel = compile(context);

        return queue.enqueue_1d_range_kernel(
                   kernel,
                   global_work_offset,
                   global_work_size,
                   local_work_size,
                   events
               );
    }

    template<class T>
    std::string get_buffer_identifier(const buffer &buffer,
                                      const memory_object::address_space address_space =
                                          memory_object::global_memory)
    {
        // check if we've already seen buffer
        for(size_t i = 0; i < m_stored_buffers.size(); i++){
            const detail::meta_kernel_buffer_info &bi = m_stored_buffers[i];

            if(bi.m_mem == buffer.get() &&
               bi.address_space == address_space){
                return bi.identifier;
            }
        }

        // create a new binding
        std::string identifier =
            "_buf" + lexical_cast<std::string>(m_stored_buffers.size());
        size_t index = add_arg<T *>(address_space, identifier);

        // store new buffer info
        m_stored_buffers.push_back(
            detail::meta_kernel_buffer_info(buffer, identifier, address_space, index));

        return identifier;
    }

    template<class T>
    std::string get_svm_identifier(const svm_ptr<T> &svm_ptr,
                                   const memory_object::address_space address_space =
                                       memory_object::global_memory)
    {
        BOOST_ASSERT(
            (address_space == memory_object::global_memory)
                || (address_space == memory_object::constant_memory)
        );

        // check if we've already seen this pointer
        for(size_t i = 0; i < m_stored_svm_ptrs.size(); i++){
            const detail::meta_kernel_svm_info &spi = m_stored_svm_ptrs[i];

            if(spi.ptr == svm_ptr.get() &&
               spi.address_space == address_space){
                return spi.identifier;
            }
        }

        // create a new binding
        std::string identifier =
            "_svm_ptr" + lexical_cast<std::string>(m_stored_svm_ptrs.size());
        size_t index = add_arg<T *>(address_space, identifier);

        if(m_stored_svm_ptrs.empty()) {
            m_options += std::string(" -cl-std=CL2.0");
        }

        // store new svm pointer info
        m_stored_svm_ptrs.push_back(
            detail::meta_kernel_svm_info(
                svm_ptr, identifier, address_space, index
            )
        );

        return identifier;
    }

    std::string get_image_identifier(const char *qualifiers, const image2d &image)
    {
        size_t index = add_arg_with_qualifiers<image2d>(qualifiers, "image");

        set_arg(index, image);

        return "image";
    }

    std::string get_sampler_identifier(bool normalized_coords,
                                       cl_addressing_mode addressing_mode,
                                       cl_filter_mode filter_mode)
    {
        (void) normalized_coords;
        (void) addressing_mode;
        (void) filter_mode;

        m_pragmas += "const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE |\n"
                     "                          CLK_ADDRESS_NONE |\n"
                     "                          CLK_FILTER_NEAREST;\n";

        return "sampler";
    }

    template<class Expr>
    static std::string expr_to_string(const Expr &expr)
    {
        meta_kernel tmp((std::string()));
        tmp << expr;
        return tmp.m_source.str();
    }

    template<class Predicate>
    detail::invoked_function<bool, boost::tuple<Predicate> > if_(Predicate pred) const
    {
        return detail::invoked_function<bool, boost::tuple<Predicate> >(
            "if", std::string(), boost::make_tuple(pred)
        );
    }

    template<class Predicate>
    detail::invoked_function<bool, boost::tuple<Predicate> > else_if_(Predicate pred) const
    {
        return detail::invoked_function<bool, boost::tuple<Predicate> >(
            "else if", std::string(), boost::make_tuple(pred)
        );
    }

    detail::meta_kernel_variable<cl_uint> get_global_id(size_t dim) const
    {
        return expr<cl_uint>("get_global_id(" + lexical_cast<std::string>(dim) + ")");
    }

    void add_function(const std::string &name, const std::string &source)
    {
        if(m_external_function_names.count(name)){
            return;
        }

        m_external_function_names.insert(name);
        m_external_function_source << source << "\n";
    }

    void add_function(const std::string &name,
                      const std::string &source,
                      const std::map<std::string, std::string> &definitions)
    {
        typedef std::map<std::string, std::string>::const_iterator iter;

        std::stringstream s;

        // add #define's
        for(iter i = definitions.begin(); i != definitions.end(); i++){
            s << "#define " << i->first;
            if(!i->second.empty()){
                s << " " << i->second;
            }
            s << "\n";
        }

        s << source << "\n";

        // add #undef's
        for(iter i = definitions.begin(); i != definitions.end(); i++){
            s << "#undef " << i->first << "\n";
        }

        add_function(name, s.str());
    }

    template<class Type>
    void add_type_declaration(const std::string &declaration)
    {
        const char *name = type_name<Type>();

        // check if the type has already been declared
        std::string source = m_type_declaration_source.str();
        if(source.find(name) != std::string::npos){
            return;
        }

        m_type_declaration_source << declaration;
    }

    template<class Type>
    void inject_type() const
    {
        inject_type_impl<Type>()(const_cast<meta_kernel &>(*this));
    }

    // the insert_function_call() method inserts a call to a function with
    // the given name tuple of argument values.
    template<class ArgTuple>
    void insert_function_call(const std::string &name, const ArgTuple &args)
    {
        *this << name << '(';
        insert_function_call_args(args);
        *this << ')';
    }

    // the insert_function_call_args() method takes a tuple of argument values
    // and inserts them into the source string with a comma in-between each.
    // this is useful for creating function calls given a tuple of values.
    void insert_function_call_args(const boost::tuple<>&)
    {
    }

    #define BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARG_TYPE(z, n, unused) \
        inject_type<BOOST_PP_CAT(T, n)>();

    #define BOOST_COMPUTE_META_KERNEL_STREAM_FUNCTION_ARG(z, n, unused) \
        << boost::get<BOOST_PP_DEC(n)>(args) << ", "

    #define BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARGS(z, n, unused) \
        template<BOOST_PP_ENUM_PARAMS(n, class T)> \
        void insert_function_call_args( \
            const boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> &args \
        ) \
        { \
            BOOST_PP_REPEAT_FROM_TO( \
                0, n, BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARG_TYPE, ~ \
            ) \
            *this \
                BOOST_PP_REPEAT_FROM_TO( \
                    1, n, BOOST_COMPUTE_META_KERNEL_STREAM_FUNCTION_ARG, ~ \
                ) \
                << boost::get<BOOST_PP_DEC(n)>(args); \
        }

    BOOST_PP_REPEAT_FROM_TO(
        1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARGS, ~
    )

    #undef BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARG_TYPE
    #undef BOOST_COMPUTE_META_KERNEL_STREAM_FUNCTION_ARG
    #undef BOOST_COMPUTE_META_KERNEL_INSERT_FUNCTION_ARGS

    static const char* address_space_prefix(const memory_object::address_space value)
    {
        switch(value){
            case memory_object::global_memory: return "__global";
            case memory_object::local_memory: return "__local";
            case memory_object::private_memory: return "__private";
            case memory_object::constant_memory: return "__constant";
        };

        return 0; // unreachable
    }

private:
    template<class T>
    size_t add_arg_with_qualifiers(const char *qualifiers, const std::string &name)
    {
        size_t index = add_arg<T>(name);

        // update argument type declaration with qualifiers
        std::stringstream s;
        s << qualifiers << " " << m_args[index];
        m_args[index] = s.str();

        return index;
    }

private:
    std::string m_name;
    std::stringstream m_source;
    std::stringstream m_external_function_source;
    std::stringstream m_type_declaration_source;
    std::set<std::string> m_external_function_names;
    std::vector<std::string> m_args;
    std::string m_pragmas;
    std::string m_options;
    std::vector<detail::meta_kernel_stored_arg> m_stored_args;
    std::vector<detail::meta_kernel_buffer_info> m_stored_buffers;
    std::vector<detail::meta_kernel_svm_info> m_stored_svm_ptrs;
};

template<class ResultType, class ArgTuple>
inline meta_kernel&
operator<<(meta_kernel &kernel, const invoked_function<ResultType, ArgTuple> &expr)
{
    if(!expr.source().empty()){
        kernel.add_function(expr.name(), expr.source(), expr.definitions());
    }

    kernel.insert_function_call(expr.name(), expr.args());

    return kernel;
}

template<class ResultType, class ArgTuple, class CaptureTuple>
inline meta_kernel&
operator<<(meta_kernel &kernel,
           const invoked_closure<ResultType, ArgTuple, CaptureTuple> &expr)
{
    if(!expr.source().empty()){
        kernel.add_function(expr.name(), expr.source(), expr.definitions());
    }

    kernel << expr.name() << '(';
    kernel.insert_function_call_args(expr.args());
    kernel << ", ";
    kernel.insert_function_call_args(expr.capture());
    kernel << ')';

    return kernel;
}

template<class Arg1, class Arg2, class Result>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_binary_operator<Arg1,
                                                             Arg2,
                                                             Result> &expr)
{
    return kernel << "((" << expr.arg1() << ")"
                  << expr.op()
                  << "(" << expr.arg2() << "))";
}

template<class T, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const detail::device_ptr_index_expr<T, IndexExpr> &expr)
{
    if(expr.m_index == 0){
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer) <<
                   '[' << expr.m_expr << ']';
    }
    else {
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer) <<
                   '[' << expr.m_index << "+(" << expr.m_expr << ")]";
    }
}

template<class T1, class T2, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const detail::device_ptr_index_expr<std::pair<T1, T2>, IndexExpr> &expr)
{
    typedef std::pair<T1, T2> T;

    if(expr.m_index == 0){
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer) <<
                   '[' << expr.m_expr << ']';
    }
    else {
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer) <<
                   '[' << expr.m_index << "+(" << expr.m_expr << ")]";
    }
}

// SVM requires OpenCL 2.0
#if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
template<class T, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const svm_ptr_index_expr<T, IndexExpr> &expr)
{
    return kernel <<
        kernel.get_svm_identifier<T>(expr.m_svm_ptr) <<
        '[' << expr.m_expr << ']';
}
#endif

template<class Predicate, class Arg>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_unary_negate_function<Predicate,
                                                                   Arg> &expr)
{
    return kernel << "!(" << expr.pred()(expr.expr()) << ')';
}

template<class Predicate, class Arg1, class Arg2>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_binary_negate_function<Predicate,
                                                                    Arg1,
                                                                    Arg2> &expr)
{
    return kernel << "!(" << expr.pred()(expr.expr1(), expr.expr2()) << ')';
}

// get<N>() for vector types
template<size_t N, class Arg, class T>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_get<N, Arg, T> &expr)
{
    BOOST_STATIC_ASSERT(N < 16);

    if(N < 10){
        return kernel << expr.m_arg << ".s" << int_(N);
    }
    else if(N < 16){
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4307)
#endif
        return kernel << expr.m_arg << ".s" << char('a' + (N - 10));
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
    }

    return kernel;
}

template<class T, class Arg>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_field<T, Arg> &expr)
{
    return kernel << expr.m_arg << "." << expr.m_field;
}

template<class T, class Arg>
inline meta_kernel& operator<<(meta_kernel &k,
                               const invoked_as<T, Arg> &expr)
{
    return k << "as_" << type_name<T>() << "(" << expr.m_arg << ")";
}

template<class T, class Arg>
inline meta_kernel& operator<<(meta_kernel &k,
                               const invoked_convert<T, Arg> &expr)
{
    return k << "convert_" << type_name<T>() << "(" << expr.m_arg << ")";
}

template<class T, class Arg>
inline meta_kernel& operator<<(meta_kernel &k,
                               const invoked_identity<T, Arg> &expr)
{
    return k << expr.m_arg;
}

template<>
struct inject_type_impl<double_>
{
    void operator()(meta_kernel &kernel)
    {
        kernel.add_extension_pragma("cl_khr_fp64", "enable");
    }
};

template<class Scalar, size_t N>
struct inject_type_impl<vector_type<Scalar, N> >
{
    void operator()(meta_kernel &kernel)
    {
        kernel.inject_type<Scalar>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_META_KERNEL_HPP

/* meta_kernel.hpp
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
*/