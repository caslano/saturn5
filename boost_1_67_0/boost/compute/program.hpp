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
BwBP2Z7tXzpsQUKBNvHW5RwLreszya4Ya+t55j310GOX6qprV5pJO8wJ0yq7tcoerbJXq4xbDsC6JdQquB/LYO1DIfceQFrRHmWwZ9vKH7GBjAgGw0MSw+f9g7kkJsZ+L5zJXSVJtG6Pzu2ejRgYaxfDz0+lUCZIWO8B3F8aiTuVdPijG2monWaR4UTXn0FuOK1ONtOFgEMpzs7uzEiZyXIgBhGpgmNB2V+cr8QtEC6CyTzMPWmWufFsjKhfKaFp8/ndqsvH/LkC55BjAkHMGDMkxCTY1cvlR3WQPitXa8JjMDhw/WGkOpiZV/GHd89yhA5JNpiS3rs/ueOzzwJjbUcKI2US/LF6E5ib8De01eACI/uNcvpHWdpEN874piyGfgpQJGzjZdpBa2bu85HuQCqFAIEgKFgo8W+ERLFqEwB+ybiElDYzZT0CBvs7Ck4C3jW1A0Y3HB7MBIUEXwgtH+rOJ1+SnO3fEdDUHRqcnZ8BsxJhGc6/V4+wEAV1t70SfyZDv0/NBv66GH9b0mS7edQuHEz4DybOhaEogNMVCeFv/9MBIiDR12Whr5dpulbT3GB46v+cZo0mBTP+9rmDVi7broyheR0ZmbLjA7A5g2U+0JK61oNMi7Cf8Z6nNuuOAoN21wMSNHT/Dqmlpfm3QnuAB1IMSknVqvcSOdhK5GCLJAdsHiIBYokJEKlTrkyk1cArY1GrcimVpNJzt8By493ykCy52MKlJN1tvO40DE40f7NY2nbWkP5L9QNUxXB9JHFbgC5tO2s1D0EUEIcEOHOPUuyWwAJqQF0ID4eqV/XKt4h7od4UMhWl0VyaQoLtUANlTHbT530lil1+3JuYZmbGR0ba7Lj4kUIOpyP/ypocmzIqZbSSETholy15GnZb1PrxXFhX1fQgbmxN3ISzC4PQ4yYI6XP36v7eoiMr0ovmdtd48/3duPw48t5px9xuDd/aivxx+ujvqcmW4wY6Ic/cvbgq6kFgjLId+e/qc1vyj8wul7sG7mSkB8dwVsB0t3jItP4NiSU2mLjv0BrzWCJu0RpxnsDDDIeB7S1Gn5EEv+o35VUFdOGo15vhGdNRvWjcKK+Vg7Dnl58x4zwqWUz3hjBNOxJzedTaWw+J623s0S9B80J20LxE6N/xqbtHdj5R3gc7bdg1g3plVn6lm8OT1biiZZ24sAcnSMgtmUGwXd0apqVX88cHEv+5vboax3lsWXb+3O58tSff784v8+bvzj8UocFrmdosp/pYUIwO49iw8+6ifTUT9LndepkbS/SeMgxhDQbpbfmHtDJ3LN3xhaZm5fuz8nc7dmmZhtohPn4YBQUKXqPP7dHLsAiyYLZV0CsL0qiyueAMp64eh+tR7qdEkQdg1Nkm7vq8z5DyAbZtrP0NHJvwDMxxMG25NkxbzgU23aAUxIy1YP7hl59BZzmKV7qY/4g3HKvN0v2dIFlQgy7as2IMLhpH0fhpGHcXxWsyT/1JqxGImiP+3bSmyAm6Xyjpdn9vzGH3x3GiIbjbNnBeqhC/q0b8q5ZaX6ICOd4l1/B45/8zOd7uxHipoGzCCRLvFwmgucJw2fZf8HCgoKXivO7qJy7cYWW03sQiDeEISziEKUW7avJS86gX64188VkWz2+EiJNf1lPUthwnA4UD6sqS4lF+o6yo1+Hvjo2QZc2CfmAsR/yqEg+co+7v+erSVYS4vwXG19ATmtVOQHxNJy2OBPpkLxZUsUI3Y3y+vxNGu6AC+TxtBX8Q/zx74UYts1s9k2ovOFauH4ZSXqVV/9wsqEuVdeYf0cZqVc6i92rSCXQJk+ZmQ5WvTOQfsdKyeW2X5g7kxLjn6FIv9YPQboHDn1XwBy0D/nXRQ6/Dnw0FsH1V94o70Efr3uK8Qx++jtqAzUF1brHH5lhk9yuNTarMVj2S8UIeYesm2DJZt8SCDZZ2UmXdMRchOZ56POvBiTF87T6T0o/ycjQeivJJcDAJS7fSzP8Q1QXCbHuI1/m8rTj8cTBrUwDimpSbGQgc/jMaw4TxYUA8cTWTzZFcI70/fDVjwuxYHyS1/QmJMQVZSmSWP8X7oJRTbKNtMxUIHacq4Vegbh86KmOeYTeoShh1MEcZ3YnPoeQ4Mh1+F7p76Ve76za7+58B8e5VsrtckN5/exX35dW/9xmJIyDr+BGeZt+8wWRFjMeS+78ss4XLSKE3cSZmshaLcGtxM7IbHwTEXBRor57z+yzacIS/g7swFBwFfZzEH3dOf2KUF1asV8uv+cEK8c0O84AnXWw/0geFqKW5vCPtJTpSkZAYB+uHqetd//KxbCxt2iSjuSNtIEup5LHgZRoZWFxWQvai1tPHcSXMvFfIAYQwcurn2nGn2SJVCQXBX1NK7TjzDuf2nRgaTogePsa991ZjOFTf3fyu5lQvV4m7OSy+Jb8Px0inyGfLnuRePhyTS4ujp5SlZahHCI1Q7JLk8QZbwUimyNzCPxZYEWlqIr6Zd9qwTu7mDzhUgDTLp/Die0UZtv/vQz2L169xXYLju3TBd/2HxNtXnjaSh24DKeQAfLiFehqo9h7I8ooZf5RL7mlAzI5gKAU74SbJ35lAz6+lGyazxH6qi0hQTS8qEzjHD4ZHYyM6xK4hgpLPlIRIyafeIjImxKXL5JmdToJhYHyFuP8bUKC5O2wH3GG4C+41qf+DcVcy4CNBv9h/BUlDNa5utUCfSwzOTW8Dt688QezS7c6GXcqQhpMkbPDjcH3MLjE6cpx4VZLnsmmuqxYkUI/W2R15ItemZFR2PXbraSNpnFcO42BWI2A6dcKUcA6JHITchFXwJTTsaCPYVZ4boolntFKnlBBMWFBnS1iQQpgynddhy0aswy+vAFcZ1xpX8n5KRK5eioN2CzLsEjKijcVmE3LKzXiU4FgkgWZ/dFojkEprwjEBBhUQn3YhtccuD9Q9Z81zpPLy5HmZp/5FPixI8P211qCDIYzaHHPlGb0mnr+hno8w0V36anaKiWUQxst1cOZk4U6ubg+GmJoyE1WdLs89pcjKHHHKyBfIod8byyZ0yQqbl1ZiHqFLLF0czyXA3m/SiBORnVv40Dajquu5Po5eYJ2BDZD0yy8nbDeUnOr4VqKCbeK2D5kyuHFMt6DKeLnNbh6PA3fvpIpSEGQUleU7ICqXaZa7nI+IL+eZrkqJOzogDLD7v2FFUtp4MxceSboABiz50yFH/6CzD84AxuEKaQpU15Wrp+B4QBk2hSDaplw0Ba4J1AlYEUtWKWgJBmLeUDA1JQCb0DNspZx0Ra+PDoVHweN6D1Cxm8U+edhMwHqqfcElLbR1n2q/V6T/awBzOOcrERO2wg/QScI8EkTZn+QP3oX8v5nk/82auiX1wADWKWqPpvZqalyeDmjqXk1t09SDCe+3ErLYK/tSE64h9UPrmYawHdMfrDDUrYSyHA1CDP8OnGmJ5/6LsKay+e67NYf+FNak6JCn/leWQPlYSlXS4mBHQMYmsAwEEGBJFkzha8YRq+XzH6whlm1rvv+gY3/RrhVTdf/RIn+vp2mxZE5jVxLv5fMfMTMd4Uw5ur+d5E1P052SW0UcdEr3NBUxM7GF+kB9py70/lQeS0I5tYutavZ56kejL2OYKllHdQ67HAlJ8YvNsVyoGoQ/PoYl2UzylqZu/ailaHfNFcRwftyun8jvyUd09uZj/matrPnj9NIXs7wd++ktVkUDqr1eb/u4HTnKkANMalmHzESjpETO+slpWvFP+j7ZH1sIt3Zze6j+a4lvteo/fqH6PzlN/O5cWexampbaq2RTx62mBD1bTcWtpmLPfvwRjeWTjzgWuUevODfgeG/RFxIwmwMvQvsgqzlr+EivWHcpTD/A0MM/f7dxs9KeTWg1LCsN8TILTkZq3IamnlGJWxEbSCzU/G6x7gFTXWrRjXEi4F62zYj6e+DiyA3kCLwEU65f3kZf93pjY6zQc93Vk/jD8/whS4J52F4RLTvO6oM7vHD706O3M/MTAKjdpJcdL2JFp4Rlk6lMdcOEhIrVODzuExsvZQ8/uiP6FECtvPqGl8C4GYE5SGrnJK+ZVEpJb+GKpqK6e4OZVNfqsu5saMN1RJsEF2kxvweQ1MNJL29IVtyEa53y6tWpSRM5l5KatIiT7rOScMR7SEZXFLnLQUSO6z0N+7tGQGXcXJqzl0BJYeC6PD5CrssxXpdKrMshkfFPuS62+811OXr9v1uX0bd+zbqcnSLXhQ2jYOUml2WcRy5LXGoouoFep2yW8LeIz5aIQSnaQ0xIRjBxul0SbeI5T+BfrFD8579StrZxIBy4yje2MevSJENwYtbFdz+ztlxjGxZTz5SreRiGzplmzXI1KWkikvjeU64mksyb0Uy5fpRSaGzrkSkvmymTwFhlyqXj120TZQYlmbJIptxnpRQcS126+540lw4zneKuwoTRNVclYLTuKoZR+yUMo2Fv821Y4osvZm/ohm/KkU9g91zQ0nUSyuMOY+1z1PDPsJWpwwbIAh2t/s6JX5CoVCM4Vu7KjWZozJ2/Om2IswtMEHjv2rix86nbCcBZw8dG6WaIoMFSoXHxTXHYLrbCVusw7ULevX0crPvm6bRU4RdC8Eb2wTtrb4czn91VzPIPDnHJW7gkQcHzMlL0XioW/hG0TVCihUusHVDCeV6JZ1DiB1aJp2+XLkhTS7x/44ASnnq2IqFS66xSz3Cp8QNKrT+/1FWs2d0TCv/QLBadJTXOvsiLG8lp1W/OkTvbIBKzXuCM8uMROede6ybPvFtAtnUp2QCN+pRced+Vl6iDHn4kH1wy+4eU8sOUcim3vemHIEFoxG7wlzVWw34EVh8RaXY7wayh4R+kVLBYZrvkgk1yxg+T2nGUMYOSX4jlJntNYx6TWhXNgEvWYBZMguGgRN3mGbZVIDkmPiCiT0KqPeTQ9sEO2TpNmBXKG+wDdwTYpqEAed2uL8kN24JmoFmqJpBVAe5TCm5qesHJkthvzSPwbjn73RHjB576u3AKbvzQU/8Nfljnqb+CH37kqe/EfY/xgqfhucQRsCnfDyL59VwY/ib0PQEWdsWag6dN7xyeeo3v93C99xq7ZGw4qTwhqRyIC6sU0woZz2xmmtdNFd4DlOEc3bKFb+mZALVuVNIiFadukRk2Sc6kyUiQzpdlSsM/bMy+BJiBgYZC1zHrstX2NTI/myalLq2n/vWUG+c880roWZt1aYCp6KpPFGrHZeEy+dyB50UDAGp2yrXJrFEQc8UjBKT3HThtelbx1OfCddP5UHzbAVMOrrfjs5fVQIBEMTeGg9ywDDsPKqp+IeOQd45i9chwXnMYxPGhUTCWzIYebU0WLGv9efAqcURk38tErkN0j6cNC4qzJ9UbqxfSZoBorG+vRlC+0LX9nIepn3IL6PBRS930X7lxIzaoAjW8S18M9YjuzzHUXC2ymEUxlZryhhAKMSNQcJKY5w7EeHKJs/czWI/SyzpA0n+ZyyT99lGsVW8apeRAlC9rx4soaSfGfnspH4pY4dEypV/4jdHtrguncy0yUR0a3Y6FNz8Ri8xuUIpzOejeAW3aHPFRzEihYw0c9VpxB81b/5uuyrARAnXdaak+0CANNceKgWyGdw7bhEarVbk7h+TK5nWY+u+NZDvVSHzIksf1I4+8XxhVBjv1NXXFgKv96tXVUNcTL7xp6py4eRH2K5ni0uN2m+VeLzZCrG8D7LQdIdDI2w/QgA9Iu95GeceWVy96jvDPvd9Uc3Hh6v3gZxmWUqH4r5Ey3C2Jlm/i9pqw8ZqQXuvSbwklDnZIyOXrQuPm5cQfheSdH4FDu6WyheNlPYNyVkeW5doIsBcnAPvxESySOgv2xxx6ae4ry9rZK8l46lxe2FYeXY0TaPFyB+sRj9CH4nugbhenXjqWZnQYG9Ppw1LdF14l9ZtoIndgIn0j4JGgGB6qivxeZbCjZVqkf8jyL2PpkX6D9/tPbKyBpw8rOqxc5HsilxZY1go/gmat2q2ydUoaGqwQYOyp4+NjLXIdRmzpgyNHr3TkOAii8CfJZdAyqKOVbqrKEUwIao04gZuCyQrbq2H8jnn58JW73sn2QvXco98SoJnNdvJpgPFhwzGiYnfm0kCvt6bpquQU1RxjTews2UkiHeYkvbTVjsEL9wjJ9DibP8ecjBuO4GfEvLJ7b6j5sWMyj90mpwoTNdTRMiNi0ER1xZmYGzIKpe7PYiv6L8clXEkQhWDma0/CuqHMKwpujxvcUTCwxIve9YhR6Juf6VSmEWbD5oNIud9NQ7/cmXJXHBuHEJdfTY/6vcxeXHsT+6bQS3qLw2kBcS0JVBKip+ZRG7dVEOJ2vgo50y1B+8Z9cmsp6leuoHbLqevag269IyAKxpnq/44UNcwyL6jKvJw4+7gI5IBmZSHJT4+i1SttKuoE7ypqeqTNiA2LLGNjBtN0Uatb7cTHZaP0upX8pAwB2KvWYS2BLzQ4xQuf9SXcnkrdmGgjh52qfqYYbNXzRGGjrAYXqH6aUyKcspxTnuWUxzgFLHVgu1KMoyxRxUlQ8gtU13CmuzilnVOWc8o3OQW9CFTXcsp4TlGQQnX8kd7q9tGwSDQ7xt/b7jW1x9hA6OkggdBnwyAakRgAMPtDX4Ytlh1tWo+RLXjprPQh7+Wzz9nOyM5NYJ3UP+mNmBJ4xNtQTw+lCHzTvuKO8GLx/mbGn242uDEx6Me/IQQniUd67zwszUlCZovv/isDz9zgIy+fNaYVVfbUbmNNkm1QojZGZRHYiCyPNPVxjqSX64clVM730k7V6j8zBJoGVr9f3/C1/W5qo4dIl1dMuZhAg7MTWA/ioepNy8yPufRRb1LMtxGc1SazZog/zqAp5r4jKIqY151hizYtlK9OsYO/YiXZrm/nt/BqqruniW/xV5fdtBV4il8BLLyXrpwh/eWTGDqMplHkDmN1Q74GblyOCZ83OUQCzs610By+1LfzOfx1+XYepL/qUN+UYvZDZ8Gn7IY4/ac+KrIGWS/y7cS6KcN9O9fh76CiP6Vm5/U4kMyeK5eZVnG0WWCYb1muel4pDF08nyw1PlFqrG8ncGj5vyvNKBRKlh5udvG8bJgycQNn48GOtUYkJ4bIi/D8GpR8WSYVdBQYM0JyYkX/J33wm9jY7LSOqwFP8paoAqe/+olIE7ppVJ/Avcc22A63NqLDfA8idWYOCYXjFpqT5Cegtfx5cQcK9vtKU+yey8vNytjGoxHVa02o0qquqisP9VU3jxhB8Nw2BPBMTNR68fL7uOLEGCUGHVZGmX1HkEdRPzHN1rWfz9fRrG/ZZKVML3Xr81yhUEhb5pLJodZiqNeypx1ZWCtbpzcxCA1HPcbsbBOiytZp88xSWqk79hhm8vdvcrTnotbl95vTfI/euNeJC/AdKNPUgucmVBwKlEf9a7bDCRnMRP/xkGntDXUeEnvXUWPGNi50wNjGPRG7V8Iwdg2ypwXMmDI08P73COJvH5KqYDv0TFLBduumpIJt5BUggK21bo25SF0fnmEtQ41TtDp87tpDaZFX1sica62cb1Bq2Ns8A9MuBmHaxZQ3+ozqJ4pZu/bnf+wjqZcYjD0cyr6HXa9M3UoZnpQZNMqgxwtaivrZK5LymSiY3wdqc5m4hh6I2g051mfwvU/DLmVwsBwH4LdSksQKCT9ULjcgftebgRqV08RRblud+CjEF0SD84NiakefETRB/2Z69m1ApprhcGks8vARJn38gdHrShMm5k1Ws4PAgBQYNDflMYjrmARzmUpZfRt4mceG9EO+DUxdMnnAsXSeGLHooz4jdlNBi/xoeiRFHKBQ9f+W83LHR9xZDEBj+iS+h0EzzAXDgyK7Joow5ide1L/8YZnMVwf4UPdt4u2Z3LIX/RHXyJMeAgzs2M9mxc16CKf9nVzipftRArQ8YFoaiQ4+w+y0SlVSqdgoOSORlolm9WIbch0SYy5le1TW8QfRL5cNGI/lQsiC5OLbwMR1EE/2W1h0c3KzzbRXKS26k3HA2Laep3gxroorzIuib3zWb7wybxcc782n37D3Hm2u0OZ2F+1e4UBgxXfpT1k3ruwFYssApXRGL4e/W2NsE3aCDIDPbUYfy3ReV8oemJ9p7oEke1Q7bwMj8tM+luAk4ZNbo7gt3me8s/BXI73aTqSmbD7j6Iu2E68pG5SXEluZNel9g5i15EZ26hQ+4NW5Gx8SG94np1ANXlM2Re0v2BQTW+ZvOY/5mileuwsyJ6+IUC9mm0SXeEomYjXEfdh/2bWPJhkNf5bWWM8P2eHByW1b28B0qxFLJZQfnjUKUNdgjZdF27mDf1v4lyc0X7YBuBFnLopTn0BopRU0FRxC1DYruaGUfJsY/kbk8D3pxI7DO8+IZIYXN/OOwyFm2MpuncybdGQnSb8+za01AsHMHXuCPi0XMTSCDecMIpLeaOk80XCYRaMMbWcyozraovLZ6hB9Gk0GECs2uLXRImfvgEsPmVN5x9VxI2TO4K1Xszz9STozugQzjwJmTjlNmIk25Q5nI710oE73rn7Cphsc5orOGeOgxctKM1d+7ims5csWhDTeCp5logVFS/m12WJhqm9NsDC/mEycdmW6RdDDRvVW6sPCV3BTGihvnj+WWh7zqcuWuNQD/0y7XO/CV5FFe7AHm+tK3lz5GJJ9c//mlyDQPt6xPS9SmtKtL5ujzwsw5EvuOBpt+RSOn3bQr7jxXcKKjT30aGtt6KY/iGUQjXZ8Kv0PiCdxVvubvfLVkQiphe/i3v19Rigov1pxiqKoQ4w62Md+XWAxYPwGtRu/OY4P0YOgeuj1Oy0tLbaQ1nAUyY2F/YSbHbbIg8dtWkP7pxyJFJ30ixDuG2WDWmWnmDnnNJxdFOwvl9WA/WnY/ClskJ9agNj0nvqRkHD4Y8peK3eQBlQTCgXE/CcMsx9W6efhmuM33DSniy8K+qkX6F5KwPuAOY7fH7C2LGn5F40+92lqhDWiasdYiB7reev5n6JS++zo85ib2RXyyJUqnRF7xPNWA74iijE+0kB7Uf1wd6ZNPjLI/YF2d0y/TILr7Uwx46xhxPJFMbzt8wzLbsuBitn/AX9AoVQZIWVRr2wj4swrxaGpEusuGmlvkeAhwbUNnhV6F2o4oLLdTVwhnGX/Qaz5ABp2yTDVd80+bTRPcLjY0rgbqLTZDlQK28VP+qg=
*/