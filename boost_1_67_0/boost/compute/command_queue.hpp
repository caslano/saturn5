//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_COMMAND_QUEUE_HPP
#define BOOST_COMPUTE_COMMAND_QUEUE_HPP

#include <cstddef>
#include <algorithm>

#include <boost/assert.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/image/image1d.hpp>
#include <boost/compute/image/image2d.hpp>
#include <boost/compute/image/image3d.hpp>
#include <boost/compute/image/image_object.hpp>
#include <boost/compute/utility/wait_list.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>
#include <boost/compute/detail/diagnostic.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {
namespace detail {

inline void BOOST_COMPUTE_CL_CALLBACK
nullary_native_kernel_trampoline(void *user_func_ptr)
{
    void (*user_func)();
    std::memcpy(&user_func, user_func_ptr, sizeof(user_func));
    user_func();
}

} // end detail namespace

/// \class command_queue
/// \brief A command queue.
///
/// Command queues provide the interface for interacting with compute
/// devices. The command_queue class provides methods to copy data to
/// and from a compute device as well as execute compute kernels.
///
/// Command queues are created for a compute device within a compute
/// context.
///
/// For example, to create a context and command queue for the default device
/// on the system (this is the normal set up code used by almost all OpenCL
/// programs):
/// \code
/// #include <boost/compute/core.hpp>
///
/// // get the default compute device
/// boost::compute::device device = boost::compute::system::default_device();
///
/// // set up a compute context and command queue
/// boost::compute::context context(device);
/// boost::compute::command_queue queue(context, device);
/// \endcode
///
/// The default command queue for the system can be obtained with the
/// system::default_queue() method.
///
/// \see buffer, context, kernel
class command_queue
{
public:
    enum properties {
        enable_profiling = CL_QUEUE_PROFILING_ENABLE,
        enable_out_of_order_execution = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        ,
        on_device = CL_QUEUE_ON_DEVICE,
        on_device_default = CL_QUEUE_ON_DEVICE_DEFAULT
        #endif
    };

    enum map_flags {
        map_read = CL_MAP_READ,
        map_write = CL_MAP_WRITE
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        ,
        map_write_invalidate_region = CL_MAP_WRITE_INVALIDATE_REGION
        #endif
    };

    #ifdef BOOST_COMPUTE_CL_VERSION_1_2
    enum mem_migration_flags {
        migrate_to_host = CL_MIGRATE_MEM_OBJECT_HOST,
        migrate_content_undefined = CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED
    };
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Creates a null command queue.
    command_queue()
        : m_queue(0)
    {
    }

    explicit command_queue(cl_command_queue queue, bool retain = true)
        : m_queue(queue)
    {
        if(m_queue && retain){
            clRetainCommandQueue(m_queue);
        }
    }

    /// Creates a command queue in \p context for \p device with
    /// \p properties.
    ///
    /// \see_opencl_ref{clCreateCommandQueue}
    command_queue(const context &context,
                  const device &device,
                  cl_command_queue_properties properties = 0)
    {
        BOOST_ASSERT(device.id() != 0);

        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        if (device.check_version(2, 0)){
            std::vector<cl_queue_properties> queue_properties;
            if(properties){
                queue_properties.push_back(CL_QUEUE_PROPERTIES);
                queue_properties.push_back(cl_queue_properties(properties));
                queue_properties.push_back(cl_queue_properties(0));
            }

            const cl_queue_properties *queue_properties_ptr =
                queue_properties.empty() ? 0 : &queue_properties[0];

            m_queue = clCreateCommandQueueWithProperties(
                context, device.id(), queue_properties_ptr, &error
            );
        } else
        #endif
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            m_queue = clCreateCommandQueue(
                context, device.id(), properties, &error
            );
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(!m_queue){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new command queue object as a copy of \p other.
    command_queue(const command_queue &other)
        : m_queue(other.m_queue)
    {
        if(m_queue){
            clRetainCommandQueue(m_queue);
        }
    }

    /// Copies the command queue object from \p other to \c *this.
    command_queue& operator=(const command_queue &other)
    {
        if(this != &other){
            if(m_queue){
                clReleaseCommandQueue(m_queue);
            }

            m_queue = other.m_queue;

            if(m_queue){
                clRetainCommandQueue(m_queue);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new command queue object from \p other.
    command_queue(command_queue&& other) BOOST_NOEXCEPT
        : m_queue(other.m_queue)
    {
        other.m_queue = 0;
    }

    /// Move-assigns the command queue from \p other to \c *this.
    command_queue& operator=(command_queue&& other) BOOST_NOEXCEPT
    {
        if(m_queue){
            clReleaseCommandQueue(m_queue);
        }

        m_queue = other.m_queue;
        other.m_queue = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the command queue.
    ///
    /// \see_opencl_ref{clReleaseCommandQueue}
    ~command_queue()
    {
        if(m_queue){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseCommandQueue(m_queue)
            );
        }
    }

    /// Returns the underlying OpenCL command queue.
    cl_command_queue& get() const
    {
        return const_cast<cl_command_queue &>(m_queue);
    }

    /// Returns the device that the command queue issues commands to.
    device get_device() const
    {
        return device(get_info<cl_device_id>(CL_QUEUE_DEVICE));
    }

    /// Returns the context for the command queue.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_QUEUE_CONTEXT));
    }

    /// Returns information about the command queue.
    ///
    /// \see_opencl_ref{clGetCommandQueueInfo}
    template<class T>
    T get_info(cl_command_queue_info info) const
    {
        return detail::get_object_info<T>(clGetCommandQueueInfo, m_queue, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<command_queue, Enum>::type
    get_info() const;

    /// Returns the properties for the command queue.
    cl_command_queue_properties get_properties() const
    {
        return get_info<cl_command_queue_properties>(CL_QUEUE_PROPERTIES);
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns the current default device command queue for the underlying device.
    ///
    /// \opencl_version_warning{2,1}
    command_queue get_default_device_queue() const
    {
        return command_queue(get_info<cl_command_queue>(CL_QUEUE_DEVICE_DEFAULT));
    }

    /// Replaces the default device command queue for the underlying device
    /// with this command queue. Command queue must have been created
    /// with CL_QUEUE_ON_DEVICE flag.
    ///
    /// \see_opencl21_ref{clSetDefaultDeviceCommandQueue}
    ///
    /// \opencl_version_warning{2,1}
    void set_as_default_device_queue() const
    {
        cl_int ret = clSetDefaultDeviceCommandQueue(
            this->get_context().get(),
            this->get_device().get(),
            m_queue
        );
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Enqueues a command to read data from \p buffer to host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadBuffer}
    ///
    /// \see copy()
    event enqueue_read_buffer(const buffer &buffer,
                              size_t offset,
                              size_t size,
                              void *host_ptr,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read data from \p buffer to host memory. The
    /// copy will be performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueReadBuffer}
    ///
    /// \see copy_async()
    event enqueue_read_buffer_async(const buffer &buffer,
                                    size_t offset,
                                    size_t size,
                                    void *host_ptr,
                                    const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to read a rectangular region from \p buffer to
    /// host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_read_buffer_rect(const buffer &buffer,
                                   const size_t buffer_origin[3],
                                   const size_t host_origin[3],
                                   const size_t region[3],
                                   size_t buffer_row_pitch,
                                   size_t buffer_slice_pitch,
                                   size_t host_row_pitch,
                                   size_t host_slice_pitch,
                                   void *host_ptr,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBufferRect(
            m_queue,
            buffer.get(),
            CL_TRUE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read a rectangular region from \p buffer to
    /// host memory. The copy will be performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueReadBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_read_buffer_rect_async(const buffer &buffer,
                                         const size_t buffer_origin[3],
                                         const size_t host_origin[3],
                                         const size_t region[3],
                                         size_t buffer_row_pitch,
                                         size_t buffer_slice_pitch,
                                         size_t host_row_pitch,
                                         size_t host_slice_pitch,
                                         void *host_ptr,
                                         const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBufferRect(
            m_queue,
            buffer.get(),
            CL_FALSE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Enqueues a command to write data from host memory to \p buffer.
    ///
    /// \see_opencl_ref{clEnqueueWriteBuffer}
    ///
    /// \see copy()
    event enqueue_write_buffer(const buffer &buffer,
                               size_t offset,
                               size_t size,
                               const void *host_ptr,
                               const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to write data from host memory to \p buffer.
    /// The copy is performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueWriteBuffer}
    ///
    /// \see copy_async()
    event enqueue_write_buffer_async(const buffer &buffer,
                                     size_t offset,
                                     size_t size,
                                     const void *host_ptr,
                                     const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to write a rectangular region from host memory
    /// to \p buffer.
    ///
    /// \see_opencl_ref{clEnqueueWriteBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_write_buffer_rect(const buffer &buffer,
                                    const size_t buffer_origin[3],
                                    const size_t host_origin[3],
                                    const size_t region[3],
                                    size_t buffer_row_pitch,
                                    size_t buffer_slice_pitch,
                                    size_t host_row_pitch,
                                    size_t host_slice_pitch,
                                    void *host_ptr,
                                    const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBufferRect(
            m_queue,
            buffer.get(),
            CL_TRUE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to write a rectangular region from host memory
    /// to \p buffer. The copy is performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueWriteBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_write_buffer_rect_async(const buffer &buffer,
                                          const size_t buffer_origin[3],
                                          const size_t host_origin[3],
                                          const size_t region[3],
                                          size_t buffer_row_pitch,
                                          size_t buffer_slice_pitch,
                                          size_t host_row_pitch,
                                          size_t host_slice_pitch,
                                          void *host_ptr,
                                          const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBufferRect(
            m_queue,
            buffer.get(),
            CL_FALSE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Enqueues a command to copy data from \p src_buffer to
    /// \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyBuffer}
    ///
    /// \see copy()
    event enqueue_copy_buffer(const buffer &src_buffer,
                              const buffer &dst_buffer,
                              size_t src_offset,
                              size_t dst_offset,
                              size_t size,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(src_offset + size <= src_buffer.size());
        BOOST_ASSERT(dst_offset + size <= dst_buffer.size());
        BOOST_ASSERT(src_buffer.get_context() == this->get_context());
        BOOST_ASSERT(dst_buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueCopyBuffer(
            m_queue,
            src_buffer.get(),
            dst_buffer.get(),
            src_offset,
            dst_offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to copy a rectangular region from
    /// \p src_buffer to \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_copy_buffer_rect(const buffer &src_buffer,
                                   const buffer &dst_buffer,
                                   const size_t src_origin[3],
                                   const size_t dst_origin[3],
                                   const size_t region[3],
                                   size_t buffer_row_pitch,
                                   size_t buffer_slice_pitch,
                                   size_t host_row_pitch,
                                   size_t host_slice_pitch,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(src_buffer.get_context() == this->get_context());
        BOOST_ASSERT(dst_buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueCopyBufferRect(
            m_queue,
            src_buffer.get(),
            dst_buffer.get(),
            src_origin,
            dst_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to fill \p buffer with \p pattern.
    ///
    /// \see_opencl_ref{clEnqueueFillBuffer}
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see fill()
    event enqueue_fill_buffer(const buffer &buffer,
                              const void *pattern,
                              size_t pattern_size,
                              size_t offset,
                              size_t size,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueFillBuffer(
            m_queue,
            buffer.get(),
            pattern,
            pattern_size,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a command to map \p buffer into the host address space.
    /// Event associated with map operation is returned through
    /// \p map_buffer_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void* enqueue_map_buffer(const buffer &buffer,
                             cl_map_flags flags,
                             size_t offset,
                             size_t size,
                             event &map_buffer_event,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            flags,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &map_buffer_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    void* enqueue_map_buffer(const buffer &buffer,
                             cl_map_flags flags,
                             size_t offset,
                             size_t size,
                             const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_buffer(buffer, flags, offset, size, event_, events);
    }

    /// Enqueues a command to map \p buffer into the host address space.
    /// Map operation is performed asynchronously. The pointer to the mapped
    /// region cannot be used until the map operation has completed.
    ///
    /// Event associated with map operation is returned through
    /// \p map_buffer_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void* enqueue_map_buffer_async(const buffer &buffer,
                                   cl_map_flags flags,
                                   size_t offset,
                                   size_t size,
                                   event &map_buffer_event,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            flags,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &map_buffer_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// Enqueues a command to unmap \p buffer from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_buffer(const buffer &buffer,
                               void *mapped_ptr,
                               const wait_list &events = wait_list())
    {
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        return enqueue_unmap_mem_object(buffer.get(), mapped_ptr, events);
    }

    /// Enqueues a command to unmap \p mem from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_mem_object(cl_mem mem,
                                   void *mapped_ptr,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueUnmapMemObject(
            m_queue,
            mem,
            mapped_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read data from \p image to host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadImage}
    event enqueue_read_image(const image_object& image,
                             const size_t *origin,
                             const size_t *region,
                             size_t row_pitch,
                             size_t slice_pitch,
                             void *host_ptr,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueReadImage(
            m_queue,
            image.get(),
            CL_TRUE,
            origin,
            region,
            row_pitch,
            slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_read_image(const image_object& image,
                             const extents<N> origin,
                             const extents<N> region,
                             void *host_ptr,
                             size_t row_pitch = 0,
                             size_t slice_pitch = 0,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_read_image(
            image, origin3, region3, row_pitch, slice_pitch, host_ptr, events
        );
    }

    /// Enqueues a command to write data from host memory to \p image.
    ///
    /// \see_opencl_ref{clEnqueueWriteImage}
    event enqueue_write_image(image_object& image,
                              const size_t *origin,
                              const size_t *region,
                              const void *host_ptr,
                              size_t input_row_pitch = 0,
                              size_t input_slice_pitch = 0,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueWriteImage(
            m_queue,
            image.get(),
            CL_TRUE,
            origin,
            region,
            input_row_pitch,
            input_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_write_image(image_object& image,
                              const extents<N> origin,
                              const extents<N> region,
                              const void *host_ptr,
                              const size_t input_row_pitch = 0,
                              const size_t input_slice_pitch = 0,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_write_image(
            image, origin3, region3, host_ptr, input_row_pitch, input_slice_pitch, events
        );
    }

    /// Enqueues a command to map \p image into the host address space.
    ///
    /// Event associated with map operation is returned through
    /// \p map_image_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapImage}
    void* enqueue_map_image(const image_object &image,
                            cl_map_flags flags,
                            const size_t *origin,
                            const size_t *region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            event &map_image_event,
                            const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(image.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapImage(
            m_queue,
            image.get(),
            CL_TRUE,
            flags,
            origin,
            region,
            &output_row_pitch,
            &output_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &map_image_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    void* enqueue_map_image(const image_object &image,
                            cl_map_flags flags,
                            const size_t *origin,
                            const size_t *region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_image(
            image, flags, origin, region,
            output_row_pitch, output_slice_pitch, event_, events
        );
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image(image_object& image,
                            cl_map_flags flags,
                            const extents<N> origin,
                            const extents<N> region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            event &map_image_event,
                            const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_map_image(
            image, flags, origin3, region3,
            output_row_pitch, output_slice_pitch, map_image_event, events
        );
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image(image_object& image,
                            cl_map_flags flags,
                            const extents<N> origin,
                            const extents<N> region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_image(
            image, flags, origin, region,
            output_row_pitch, output_slice_pitch, event_, events
        );
    }

    /// Enqueues a command to map \p image into the host address space.
    /// Map operation is performed asynchronously. The pointer to the mapped
    /// region cannot be used until the map operation has completed.
    ///
    /// Event associated with map operation is returned through
    /// \p map_image_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapImage}
    void* enqueue_map_image_async(const image_object &image,
                                  cl_map_flags flags,
                                  const size_t *origin,
                                  const size_t *region,
                                  size_t &output_row_pitch,
                                  size_t &output_slice_pitch,
                                  event &map_image_event,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(image.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapImage(
            m_queue,
            image.get(),
            CL_FALSE,
            flags,
            origin,
            region,
            &output_row_pitch,
            &output_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &map_image_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image_async(image_object& image,
                                  cl_map_flags flags,
                                  const extents<N> origin,
                                  const extents<N> region,
                                  size_t &output_row_pitch,
                                  size_t &output_slice_pitch,
                                  event &map_image_event,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_map_image_async(
            image, flags, origin3, region3,
            output_row_pitch, output_slice_pitch, map_image_event, events
        );
    }

    /// Enqueues a command to unmap \p image from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_image(const image_object &image,
                              void *mapped_ptr,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        return enqueue_unmap_mem_object(image.get(), mapped_ptr, events);
    }

    /// Enqueues a command to copy data from \p src_image to \p dst_image.
    ///
    /// \see_opencl_ref{clEnqueueCopyImage}
    event enqueue_copy_image(const image_object& src_image,
                             image_object& dst_image,
                             const size_t *src_origin,
                             const size_t *dst_origin,
                             const size_t *region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyImage(
            m_queue,
            src_image.get(),
            dst_image.get(),
            src_origin,
            dst_origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_copy_image(const image_object& src_image,
                             image_object& dst_image,
                             const extents<N> src_origin,
                             const extents<N> dst_origin,
                             const extents<N> region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(src_image.get_context() == this->get_context());
        BOOST_ASSERT(dst_image.get_context() == this->get_context());
        BOOST_ASSERT_MSG(src_image.format() == dst_image.format(),
                         "Source and destination image formats must match.");

        size_t src_origin3[3] = { 0, 0, 0 };
        size_t dst_origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(src_origin.data(), src_origin.data() + N, src_origin3);
        std::copy(dst_origin.data(), dst_origin.data() + N, dst_origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_copy_image(
            src_image, dst_image, src_origin3, dst_origin3, region3, events
        );
    }

    /// Enqueues a command to copy data from \p src_image to \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyImageToBuffer}
    event enqueue_copy_image_to_buffer(const image_object& src_image,
                                       memory_object& dst_buffer,
                                       const size_t *src_origin,
                                       const size_t *region,
                                       size_t dst_offset,
                                       const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyImageToBuffer(
            m_queue,
            src_image.get(),
            dst_buffer.get(),
            src_origin,
            region,
            dst_offset,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to copy data from \p src_buffer to \p dst_image.
    ///
    /// \see_opencl_ref{clEnqueueCopyBufferToImage}
    event enqueue_copy_buffer_to_image(const memory_object& src_buffer,
                                       image_object& dst_image,
                                       size_t src_offset,
                                       const size_t *dst_origin,
                                       const size_t *region,
                                       const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyBufferToImage(
            m_queue,
            src_buffer.get(),
            dst_image.get(),
            src_offset,
            dst_origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to fill \p image with \p fill_color.
    ///
    /// \see_opencl_ref{clEnqueueFillImage}
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_fill_image(image_object& image,
                             const void *fill_color,
                             const size_t *origin,
                             const size_t *region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueFillImage(
            m_queue,
            image.get(),
            fill_color,
            origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_fill_image(image_object& image,
                             const void *fill_color,
                             const extents<N> origin,
                             const extents<N> region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_fill_image(
            image, fill_color, origin3, region3, events
        );
    }

    /// Enqueues a command to migrate \p mem_objects.
    ///
    /// \see_opencl_ref{clEnqueueMigrateMemObjects}
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_migrate_memory_objects(uint_ num_mem_objects,
                                         const cl_mem *mem_objects,
                                         cl_mem_migration_flags flags,
                                         const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueMigrateMemObjects(
            m_queue,
            num_mem_objects,
            mem_objects,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a kernel for execution.
    ///
    /// \see_opencl_ref{clEnqueueNDRangeKernel}
    event enqueue_nd_range_kernel(const kernel &kernel,
                                  size_t work_dim,
                                  const size_t *global_work_offset,
                                  const size_t *global_work_size,
                                  const size_t *local_work_size,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(kernel.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueNDRangeKernel(
            m_queue,
            kernel,
            static_cast<cl_uint>(work_dim),
            global_work_offset,
            global_work_size,
            local_work_size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_nd_range_kernel(const kernel &kernel,
                                  const extents<N> &global_work_offset,
                                  const extents<N> &global_work_size,
                                  const extents<N> &local_work_size,
                                  const wait_list &events = wait_list())
    {
        return enqueue_nd_range_kernel(
            kernel,
            N,
            global_work_offset.data(),
            global_work_size.data(),
            local_work_size.data(),
            events
        );
    }

    /// Convenience method which calls enqueue_nd_range_kernel() with a
    /// one-dimensional range.
    event enqueue_1d_range_kernel(const kernel &kernel,
                                  size_t global_work_offset,
                                  size_t global_work_size,
                                  size_t local_work_size,
                                  const wait_list &events = wait_list())
    {
        return enqueue_nd_range_kernel(
            kernel,
            1,
            &global_work_offset,
            &global_work_size,
            local_work_size ? &local_work_size : 0,
            events
        );
    }

    /// Enqueues a kernel to execute using a single work-item.
    ///
    /// \see_opencl_ref{clEnqueueTask}
    event enqueue_task(const kernel &kernel, const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(kernel.get_context() == this->get_context());

        event event_;

        // clEnqueueTask() was deprecated in OpenCL 2.0. In that case we
        // just forward to the equivalent clEnqueueNDRangeKernel() call.
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        size_t one = 1;
        cl_int ret = clEnqueueNDRangeKernel(
            m_queue, kernel, 1, 0, &one, &one,
            events.size(), events.get_event_ptr(), &event_.get()
        );
        #else
        cl_int ret = clEnqueueTask(
            m_queue, kernel, events.size(), events.get_event_ptr(), &event_.get()
        );
        #endif

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a function to execute on the host.
    event enqueue_native_kernel(void (BOOST_COMPUTE_CL_CALLBACK *user_func)(void *),
                                void *args,
                                size_t cb_args,
                                uint_ num_mem_objects,
                                const cl_mem *mem_list,
                                const void **args_mem_loc,
                                const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;
        cl_int ret = clEnqueueNativeKernel(
            m_queue,
            user_func,
            args,
            cb_args,
            num_mem_objects,
            mem_list,
            args_mem_loc,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Convenience overload for enqueue_native_kernel() which enqueues a
    /// native kernel on the host with a nullary function.
    event enqueue_native_kernel(void (BOOST_COMPUTE_CL_CALLBACK *user_func)(void),
                                const wait_list &events = wait_list())
    {
        return enqueue_native_kernel(
            detail::nullary_native_kernel_trampoline,
            reinterpret_cast<void *>(&user_func),
            sizeof(user_func),
            0,
            0,
            0,
            events
        );
    }

    /// Flushes the command queue.
    ///
    /// \see_opencl_ref{clFlush}
    void flush()
    {
        BOOST_ASSERT(m_queue != 0);

        cl_int ret = clFlush(m_queue);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Blocks until all outstanding commands in the queue have finished.
    ///
    /// \see_opencl_ref{clFinish}
    void finish()
    {
        BOOST_ASSERT(m_queue != 0);

        cl_int ret = clFinish(m_queue);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Enqueues a barrier in the queue.
    void enqueue_barrier()
    {
        BOOST_ASSERT(m_queue != 0);
        cl_int ret = CL_SUCCESS;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(get_device().check_version(1, 2)){
            ret = clEnqueueBarrierWithWaitList(m_queue, 0, 0, 0);
        } else
        #endif // BOOST_COMPUTE_CL_VERSION_1_2
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            ret = clEnqueueBarrier(m_queue);
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a barrier in the queue after \p events.
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_barrier(const wait_list &events)
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;
        cl_int ret = CL_SUCCESS;

        ret = clEnqueueBarrierWithWaitList(
            m_queue, events.size(), events.get_event_ptr(), &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a marker in the queue and returns an event that can be
    /// used to track its progress.
    event enqueue_marker()
    {
        event event_;
        cl_int ret = CL_SUCCESS;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(get_device().check_version(1, 2)){
            ret = clEnqueueMarkerWithWaitList(m_queue, 0, 0, &event_.get());
        } else
        #endif
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            ret = clEnqueueMarker(m_queue, &event_.get());
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a marker after \p events in the queue and returns an
    /// event that can be used to track its progress.
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_marker(const wait_list &events)
    {
        event event_;

        cl_int ret = clEnqueueMarkerWithWaitList(
            m_queue, events.size(), events.get_event_ptr(), &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to copy \p size bytes of data from \p src_ptr to
    /// \p dst_ptr.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemcpy}
    event enqueue_svm_memcpy(void *dst_ptr,
                             const void *src_ptr,
                             size_t size,
                             const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMemcpy(
            m_queue,
            CL_TRUE,
            dst_ptr,
            src_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to copy \p size bytes of data from \p src_ptr to
    /// \p dst_ptr. The operation is performed asynchronously.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemcpy}
    event enqueue_svm_memcpy_async(void *dst_ptr,
                                   const void *src_ptr,
                                   size_t size,
                                   const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMemcpy(
            m_queue,
            CL_FALSE,
            dst_ptr,
            src_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to fill \p size bytes of data at \p svm_ptr with
    /// \p pattern.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemFill}
    event enqueue_svm_fill(void *svm_ptr,
                           const void *pattern,
                           size_t pattern_size,
                           size_t size,
                           const wait_list &events = wait_list())

    {
        event event_;

        cl_int ret = clEnqueueSVMMemFill(
            m_queue,
            svm_ptr,
            pattern,
            pattern_size,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to free \p svm_ptr.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMFree}
    ///
    /// \see svm_free()
    event enqueue_svm_free(void *svm_ptr,
                           const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMFree(
            m_queue,
            1,
            &svm_ptr,
            0,
            0,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to map \p svm_ptr to the host memory space.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMap}
    event enqueue_svm_map(void *svm_ptr,
                          size_t size,
                          cl_map_flags flags,
                          const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMap(
            m_queue,
            CL_TRUE,
            flags,
            svm_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to unmap \p svm_ptr from the host memory space.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMUnmap}
    event enqueue_svm_unmap(void *svm_ptr,
                            const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMUnmap(
            m_queue,
            svm_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_0

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to indicate which device a set of ranges of SVM allocations
    /// should be associated with. The pair \p svm_ptrs[i] and \p sizes[i] together define
    /// the starting address and number of bytes in a range to be migrated.
    ///
    /// If \p sizes is empty, then that means every allocation containing any \p svm_ptrs[i]
    /// is to be migrated. Also, if \p sizes[i] is zero, then the entire allocation containing
    /// \p svm_ptrs[i] is migrated.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clEnqueueSVMMigrateMem}
    event enqueue_svm_migrate_memory(const std::vector<const void*> &svm_ptrs,
                                     const std::vector<size_t> &sizes,
                                     const cl_mem_migration_flags flags = 0,
                                     const wait_list &events = wait_list())
    {
        BOOST_ASSERT(svm_ptrs.size() == sizes.size() || sizes.size() == 0);
        event event_;

        cl_int ret = clEnqueueSVMMigrateMem(
            m_queue,
            static_cast<cl_uint>(svm_ptrs.size()),
            const_cast<void const **>(&svm_ptrs[0]),
            sizes.size() > 0 ? &sizes[0] : NULL,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to indicate which device a range of SVM allocation
    /// should be associated with. The pair \p svm_ptr and \p size together define
    /// the starting address and number of bytes in a range to be migrated.
    ///
    /// If \p size is 0, then the entire allocation containing \p svm_ptr is
    /// migrated. The default value for \p size is 0.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clEnqueueSVMMigrateMem}
    event enqueue_svm_migrate_memory(const void* svm_ptr,
                                     const size_t size = 0,
                                     const cl_mem_migration_flags flags = 0,
                                     const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMigrateMem(
            m_queue,
            cl_uint(1),
            &svm_ptr,
            &size,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Returns \c true if the command queue is the same at \p other.
    bool operator==(const command_queue &other) const
    {
        return m_queue == other.m_queue;
    }

    /// Returns \c true if the command queue is different from \p other.
    bool operator!=(const command_queue &other) const
    {
        return m_queue != other.m_queue;
    }

    /// \internal_
    operator cl_command_queue() const
    {
        return m_queue;
    }

    /// \internal_
    bool check_device_version(int major, int minor) const
    {
        return get_device().check_version(major, minor);
    }

private:
    cl_command_queue m_queue;
};

inline buffer buffer::clone(command_queue &queue) const
{
    buffer copy(get_context(), size(), get_memory_flags());
    queue.enqueue_copy_buffer(*this, copy, 0, 0, size());
    return copy;
}

inline image1d image1d::clone(command_queue &queue) const
{
    image1d copy(
        get_context(), width(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

inline image2d image2d::clone(command_queue &queue) const
{
    image2d copy(
        get_context(), width(), height(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

inline image3d image3d::clone(command_queue &queue) const
{
    image3d copy(
        get_context(), width(), height(), depth(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

/// \internal_ define get_info() specializations for command_queue
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(command_queue,
    ((cl_context, CL_QUEUE_CONTEXT))
    ((cl_device_id, CL_QUEUE_DEVICE))
    ((uint_, CL_QUEUE_REFERENCE_COUNT))
    ((cl_command_queue_properties, CL_QUEUE_PROPERTIES))
)

#ifdef BOOST_COMPUTE_CL_VERSION_2_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(command_queue,
    ((cl_command_queue, CL_QUEUE_DEVICE_DEFAULT))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_COMMAND_QUEUE_HPP

/* command_queue.hpp
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
*/