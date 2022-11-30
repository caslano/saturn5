//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_PROGRAM_HPP
#define BOOST_COMPUTE_PROGRAM_HPP

#include <string>
#include <vector>
#include <fstream>
#include <streambuf>

#ifdef BOOST_COMPUTE_DEBUG_KERNEL_COMPILATION
#include <iostream>
#endif

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/exception/program_build_failure.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
#include <sstream>
#include <boost/optional.hpp>
#include <boost/compute/platform.hpp>
#include <boost/compute/detail/getenv.hpp>
#include <boost/compute/detail/path.hpp>
#include <boost/compute/detail/sha1.hpp>
#endif

namespace boost {
namespace compute {

class kernel;

/// \class program
/// \brief A compute program.
///
/// The program class represents an OpenCL program.
///
/// Program objects are created with one of the static \c create_with_*
/// functions. For example, to create a program from a source string:
///
/// \snippet test/test_program.cpp create_with_source
///
/// And to create a program from a source file:
/// \code
/// boost::compute::program bar_program =
///     boost::compute::program::create_with_source_file("/path/to/bar.cl", context);
/// \endcode
///
/// Once a program object has been successfully created, it can be compiled
/// using the \c build() method:
/// \code
/// // build the program
/// foo_program.build();
/// \endcode
///
/// Once the program is built, \ref kernel objects can be created using the
/// \c create_kernel() method by passing their name:
/// \code
/// // create a kernel from the compiled program
/// boost::compute::kernel foo_kernel = foo_program.create_kernel("foo");
/// \endcode
///
/// \see kernel
class program
{
public:
    /// Creates a null program object.
    program()
        : m_program(0)
    {
    }

    /// Creates a program object for \p program. If \p retain is \c true,
    /// the reference count for \p program will be incremented.
    explicit program(cl_program program, bool retain = true)
        : m_program(program)
    {
        if(m_program && retain){
            clRetainProgram(m_program);
        }
    }

    /// Creates a new program object as a copy of \p other.
    program(const program &other)
        : m_program(other.m_program)
    {
        if(m_program){
            clRetainProgram(m_program);
        }
    }

    /// Copies the program object from \p other to \c *this.
    program& operator=(const program &other)
    {
        if(this != &other){
            if(m_program){
                clReleaseProgram(m_program);
            }

            m_program = other.m_program;

            if(m_program){
                clRetainProgram(m_program);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new program object from \p other.
    program(program&& other) BOOST_NOEXCEPT
        : m_program(other.m_program)
    {
        other.m_program = 0;
    }

    /// Move-assigns the program from \p other to \c *this.
    program& operator=(program&& other) BOOST_NOEXCEPT
    {
        if(m_program){
            clReleaseProgram(m_program);
        }

        m_program = other.m_program;
        other.m_program = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the program object.
    ~program()
    {
        if(m_program){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseProgram(m_program)
            );
        }
    }

    /// Returns the underlying OpenCL program.
    cl_program& get() const
    {
        return const_cast<cl_program &>(m_program);
    }

    /// Returns the source code for the program.
    std::string source() const
    {
        return get_info<std::string>(CL_PROGRAM_SOURCE);
    }

    /// Returns the binary for the program.
    std::vector<unsigned char> binary() const
    {
        size_t binary_size = get_info<size_t>(CL_PROGRAM_BINARY_SIZES);
        std::vector<unsigned char> binary(binary_size);

        unsigned char *binary_ptr = &binary[0];
        cl_int error = clGetProgramInfo(m_program,
                                        CL_PROGRAM_BINARIES,
                                        sizeof(unsigned char **),
                                        &binary_ptr,
                                        0);
        if(error != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return binary;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns the SPIR-V binary for the program.
    std::vector<unsigned char> il_binary() const
    {
        return get_info<std::vector<unsigned char> >(CL_PROGRAM_IL);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    std::vector<device> get_devices() const
    {
        std::vector<cl_device_id> device_ids =
            get_info<std::vector<cl_device_id> >(CL_PROGRAM_DEVICES);

        std::vector<device> devices;
        for(size_t i = 0; i < device_ids.size(); i++){
            devices.push_back(device(device_ids[i]));
        }

        return devices;
    }

    /// Returns the context for the program.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_PROGRAM_CONTEXT));
    }

    /// Returns information about the program.
    ///
    /// \see_opencl_ref{clGetProgramInfo}
    template<class T>
    T get_info(cl_program_info info) const
    {
        return detail::get_object_info<T>(clGetProgramInfo, m_program, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<program, Enum>::type
    get_info() const;

    /// Returns build information about the program.
    ///
    /// For example, this function can be used to retreive the options used
    /// to build the program:
    /// \code
    /// std::string build_options =
    ///     program.get_build_info<std::string>(CL_PROGRAM_BUILD_OPTIONS);
    /// \endcode
    ///
    /// \see_opencl_ref{clGetProgramInfo}
    template<class T>
    T get_build_info(cl_program_build_info info, const device &device) const
    {
        return detail::get_object_info<T>(clGetProgramBuildInfo, m_program, info, device.id());
    }

    /// Builds the program with \p options.
    ///
    /// If the program fails to compile, this function will throw an
    /// opencl_error exception.
    /// \code
    /// try {
    ///     // attempt to compile to program
    ///     program.build();
    /// }
    /// catch(boost::compute::opencl_error &e){
    ///     // program failed to compile, print out the build log
    ///     std::cout << program.build_log() << std::endl;
    /// }
    /// \endcode
    ///
    /// \see_opencl_ref{clBuildProgram}
    void build(const std::string &options = std::string())
    {
        const char *options_string = 0;

        if(!options.empty()){
            options_string = options.c_str();
        }

        cl_int ret = clBuildProgram(m_program, 0, 0, options_string, 0, 0);

        #ifdef BOOST_COMPUTE_DEBUG_KERNEL_COMPILATION
        if(ret != CL_SUCCESS){
            // print the error, source code and build log
            std::cerr << "Boost.Compute: "
                      << "kernel compilation failed (" << ret << ")\n"
                      << "--- source ---\n"
                      << source()
                      << "\n--- build log ---\n"
                      << build_log()
                      << std::endl;
        }
        #endif

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(program_build_failure(ret, build_log()));
        }
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Compiles the program with \p options.
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see_opencl_ref{clCompileProgram}
    void compile(const std::string &options = std::string(),
                 const std::vector<std::pair<std::string, program> > &headers =
                    std::vector<std::pair<std::string, program> >())
    {
        const char *options_string = 0;

        if(!options.empty()){
            options_string = options.c_str();
        }

        cl_int ret;
        if (headers.empty())
        {
            ret = clCompileProgram(
                m_program, 0, 0, options_string, 0, 0, 0, 0, 0
            );
        }
        else
        {
            std::vector<const char*> header_names(headers.size());
            std::vector<cl_program> header_programs(headers.size());
            for (size_t i = 0; i < headers.size(); ++i)
            {
                header_names[i] = headers[i].first.c_str();
                header_programs[i] = headers[i].second.m_program;
            }

            ret = clCompileProgram(
                m_program,
                0,
                0,
                options_string,
                static_cast<cl_uint>(headers.size()),
                header_programs.data(),
                header_names.data(),
                0,
                0
            );
        }

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Links the programs in \p programs with \p options in \p context.
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see_opencl_ref{clLinkProgram}
    static program link(const std::vector<program> &programs,
                        const context &context,
                        const std::string &options = std::string())
    {
        const char *options_string = 0;

        if(!options.empty()){
            options_string = options.c_str();
        }

        cl_int ret;
        cl_program program_ = clLinkProgram(
            context.get(),
            0,
            0,
            options_string,
            static_cast<uint_>(programs.size()),
            reinterpret_cast<const cl_program*>(&programs[0]),
            0,
            0,
            &ret
        );

        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return program(program_, false);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Returns the build log.
    std::string build_log() const
    {
        return get_build_info<std::string>(CL_PROGRAM_BUILD_LOG, get_devices().front());
    }

    /// Creates and returns a new kernel object for \p name.
    ///
    /// For example, to create the \c "foo" kernel (after the program has been
    /// created and built):
    /// \code
    /// boost::compute::kernel foo_kernel = foo_program.create_kernel("foo");
    /// \endcode
    kernel create_kernel(const std::string &name) const;

    /// Returns \c true if the program is the same at \p other.
    bool operator==(const program &other) const
    {
        return m_program == other.m_program;
    }

    /// Returns \c true if the program is different from \p other.
    bool operator!=(const program &other) const
    {
        return m_program != other.m_program;
    }

    /// \internal_
    operator cl_program() const
    {
        return m_program;
    }

    /// Creates a new program with \p source in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithSource}
    static program create_with_source(const std::string &source,
                                      const context &context)
    {
        const char *source_string = source.c_str();

        cl_int error = 0;
        cl_program program_ = clCreateProgramWithSource(context,
                                                        uint_(1),
                                                        &source_string,
                                                        0,
                                                        &error);
        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return program(program_, false);
    }

    /// Creates a new program with \p sources in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithSource}
    static program create_with_source(const std::vector<std::string> &sources,
                                      const context &context)
    {
        std::vector<const char*> source_strings(sources.size());
        for(size_t i = 0; i < sources.size(); i++){
            source_strings[i] = sources[i].c_str();
        }

        cl_int error = 0;
        cl_program program_ = clCreateProgramWithSource(context,
                                                        uint_(sources.size()),
                                                        &source_strings[0],
                                                        0,
                                                        &error);
        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return program(program_, false);
    }

    /// Creates a new program with \p file in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithSource}
    static program create_with_source_file(const std::string &file,
                                           const context &context)
    {
        // create program
        return create_with_source(read_source_file(file), context);
    }

    /// Creates a new program with \p files in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithSource}
    static program create_with_source_file(const std::vector<std::string> &files,
                                           const context &context)
    {
        std::vector<std::string> sources(files.size());

        for(size_t i = 0; i < files.size(); ++i) {
            // open file stream
            std::ifstream stream(files[i].c_str());

            if(stream.fail()){
                BOOST_THROW_EXCEPTION(std::ios_base::failure("failed to create stream."));
            }

            // read source
            sources[i] = std::string(
                    (std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>()
            );
        }

        // create program
        return create_with_source(sources, context);
    }

    /// Creates a new program with \p binary of \p binary_size in
    /// \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithBinary}
    static program create_with_binary(const unsigned char *binary,
                                      size_t binary_size,
                                      const context &context)
    {
        const cl_device_id device = context.get_device().id();

        cl_int error = 0;
        cl_int binary_status = 0;
        cl_program program_ = clCreateProgramWithBinary(context,
                                                        uint_(1),
                                                        &device,
                                                        &binary_size,
                                                        &binary,
                                                        &binary_status,
                                                        &error);
        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
        if(binary_status != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(binary_status));
        }

        return program(program_, false);
    }

    /// Creates a new program with \p binary in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithBinary}
    static program create_with_binary(const std::vector<unsigned char> &binary,
                                      const context &context)
    {
        return create_with_binary(&binary[0], binary.size(), context);
    }

    /// Creates a new program with \p file in \p context.
    ///
    /// \see_opencl_ref{clCreateProgramWithBinary}
    static program create_with_binary_file(const std::string &file,
                                           const context &context)
    {
        // open file stream
        std::ifstream stream(file.c_str(), std::ios::in | std::ios::binary);

        // read binary
        std::vector<unsigned char> binary(
            (std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>()
        );

        // create program
        return create_with_binary(&binary[0], binary.size(), context);
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Creates a new program with the built-in kernels listed in
    /// \p kernel_names for \p devices in \p context.
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see_opencl_ref{clCreateProgramWithBuiltInKernels}
    static program create_with_builtin_kernels(const context &context,
                                               const std::vector<device> &devices,
                                               const std::string &kernel_names)
    {
        cl_int error = 0;

        cl_program program_ = clCreateProgramWithBuiltInKernels(
            context.get(),
            static_cast<uint_>(devices.size()),
            reinterpret_cast<const cl_device_id *>(&devices[0]),
            kernel_names.c_str(),
            &error
        );

        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return program(program_, false);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Creates a new program with \p il_binary (SPIR-V binary)
    /// of \p il_size size in \p context.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clCreateProgramWithIL}
    static program create_with_il(const void * il_binary,
                                  const size_t il_size,
                                  const context &context)
    {
        cl_int error = 0;

        cl_program program_ = clCreateProgramWithIL(
            context.get(), il_binary, il_size, &error
        );

        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return program(program_, false);
    }

    /// Creates a new program with \p il_binary (SPIR-V binary)
    /// in \p context.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl_ref{clCreateProgramWithIL}
    static program create_with_il(const std::vector<unsigned char> &il_binary,
                                  const context &context)
    {
        return create_with_il(&il_binary[0], il_binary.size(), context);
    }

    /// Creates a new program in \p context using SPIR-V
    /// binary \p file.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl_ref{clCreateProgramWithIL}
    static program create_with_il_file(const std::string &file,
                                       const context &context)
    {
        // open file stream
        std::ifstream stream(file.c_str(), std::ios::in | std::ios::binary);

        // read binary
        std::vector<unsigned char> il(
            (std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>()
        );

        // create program
        return create_with_il(&il[0], il.size(), context);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Create a new program with \p source in \p context and builds it with \p options.
    /**
     * In case BOOST_COMPUTE_USE_OFFLINE_CACHE macro is defined,
     * the compiled binary is stored for reuse in the offline cache located in
     * $HOME/.boost_compute on UNIX-like systems and in %APPDATA%/boost_compute
     * on Windows.
     */
    static program build_with_source(
            const std::string &source,
            const context     &context,
            const std::string &options = std::string()
            )
    {
#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
        // Get hash string for the kernel.
        device   d = context.get_device();
        platform p = d.platform();

        detail::sha1 hash;
        hash.process( p.name()    )
            .process( p.version() )
            .process( d.name()    )
            .process( options     )
            .process( source      )
            ;
        std::string hash_string = hash;

        // Try to get cached program binaries:
        try {
            boost::optional<program> prog = load_program_binary(hash_string, context);

            if (prog) {
                prog->build(options);
                return *prog;
            }
        } catch (...) {
            // Something bad happened. Fallback to normal compilation.
        }

        // Cache is apparently not available. Just compile the sources.
#endif
        const char *source_string = source.c_str();

        cl_int error = 0;
        cl_program program_ = clCreateProgramWithSource(context,
                                                        uint_(1),
                                                        &source_string,
                                                        0,
                                                        &error);
        if(!program_){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        program prog(program_, false);
        prog.build(options);

#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
        // Save program binaries for future reuse.
        save_program_binary(hash_string, prog);
#endif

        return prog;
    }

    /// Create a new program with \p file in \p context and builds it with \p options.
    /**
     * In case BOOST_COMPUTE_USE_OFFLINE_CACHE macro is defined,
     * the compiled binary is stored for reuse in the offline cache located in
     * $HOME/.boost_compute on UNIX-like systems and in %APPDATA%/boost_compute
     * on Windows.
     */
    static program build_with_source_file(
            const std::string &file,
            const context     &context,
            const std::string &options = std::string()
            )
    {
        return build_with_source(read_source_file(file), context, options);
    }

private:
#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
    // Saves program binaries for future reuse.
    static void save_program_binary(const std::string &hash, const program &prog)
    {
        std::string fname = detail::program_binary_path(hash, true) + "kernel";
        std::ofstream bfile(fname.c_str(), std::ios::binary);
        if (!bfile) return;

        std::vector<unsigned char> binary = prog.binary();

        size_t binary_size = binary.size();
        bfile.write((char*)&binary_size, sizeof(size_t));
        bfile.write((char*)binary.data(), binary_size);
    }

    // Tries to read program binaries from file cache.
    static boost::optional<program> load_program_binary(
            const std::string &hash, const context &ctx
            )
    {
        std::string fname = detail::program_binary_path(hash) + "kernel";
        std::ifstream bfile(fname.c_str(), std::ios::binary);
        if (!bfile) return boost::optional<program>();

        size_t binary_size;
        std::vector<unsigned char> binary;

        bfile.read((char*)&binary_size, sizeof(size_t));

        binary.resize(binary_size);
        bfile.read((char*)binary.data(), binary_size);

        return boost::optional<program>(
                program::create_with_binary(
                    binary.data(), binary_size, ctx
                    )
                );
    }
#endif // BOOST_COMPUTE_USE_OFFLINE_CACHE

    static std::string read_source_file(const std::string &file)
    {
        // open file stream
        std::ifstream stream(file.c_str());

        if(stream.fail()){
          BOOST_THROW_EXCEPTION(std::ios_base::failure("failed to create stream."));
        }

        // read source
        return std::string(
            (std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>()
        );
    }

private:
    cl_program m_program;
};

/// \internal_ define get_info() specializations for program
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(program,
    ((cl_uint, CL_PROGRAM_REFERENCE_COUNT))
    ((cl_context, CL_PROGRAM_CONTEXT))
    ((cl_uint, CL_PROGRAM_NUM_DEVICES))
    ((std::vector<cl_device_id>, CL_PROGRAM_DEVICES))
    ((std::string, CL_PROGRAM_SOURCE))
    ((std::vector<size_t>, CL_PROGRAM_BINARY_SIZES))
    ((std::vector<unsigned char *>, CL_PROGRAM_BINARIES))
)

#ifdef BOOST_COMPUTE_CL_VERSION_1_2
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(program,
    ((size_t, CL_PROGRAM_NUM_KERNELS))
    ((std::string, CL_PROGRAM_KERNEL_NAMES))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_2

#ifdef BOOST_COMPUTE_CL_VERSION_2_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(program,
    ((std::vector<unsigned char>, CL_PROGRAM_IL))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_PROGRAM_HPP

/* program.hpp
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
*/