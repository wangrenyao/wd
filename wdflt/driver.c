
#include "private.h"


PFLT_FILTER gFilterHandle;
ULONG_PTR OperationStatusCtx = 1;
ULONG g_ulLogLevel = LOG_DEBUG;





CONST FLT_OPERATION_REGISTRATION Callbacks[] =
{

#if 0 // TODO - List all of the requests to filter.
    {
        IRP_MJ_CREATE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_CREATE_NAMED_PIPE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_CLOSE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_READ,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_WRITE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_QUERY_INFORMATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SET_INFORMATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_QUERY_EA,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SET_EA,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_FLUSH_BUFFERS,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_QUERY_VOLUME_INFORMATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SET_VOLUME_INFORMATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_DIRECTORY_CONTROL,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_FILE_SYSTEM_CONTROL,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_DEVICE_CONTROL,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_INTERNAL_DEVICE_CONTROL,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SHUTDOWN,
        0,
        wdfltPreOperationNoPostOperation,
        NULL
    },                               //post operations not supported

    {
        IRP_MJ_LOCK_CONTROL,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_CLEANUP,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_CREATE_MAILSLOT,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_QUERY_SECURITY,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SET_SECURITY,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_QUERY_QUOTA,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_SET_QUOTA,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_PNP,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_RELEASE_FOR_MOD_WRITE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_RELEASE_FOR_CC_FLUSH,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_NETWORK_QUERY_OPEN,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_MDL_READ,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_MDL_READ_COMPLETE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_PREPARE_MDL_WRITE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_MDL_WRITE_COMPLETE,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_VOLUME_MOUNT,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

    {
        IRP_MJ_VOLUME_DISMOUNT,
        0,
        wdfltPreOperation,
        wdfltPostOperation
    },

#endif // TODO

    { IRP_MJ_OPERATION_END }
};


CONST FLT_REGISTRATION FilterRegistration =
{

    sizeof ( FLT_REGISTRATION ),     //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    NULL,                               //  Context
    Callbacks,                          //  Operation callbacks

    wdfltUnload,                           //  MiniFilterUnload

    wdfltInstanceSetup,                    //  InstanceSetup
    wdfltInstanceQueryTeardown,            //  InstanceQueryTeardown
    wdfltInstanceTeardownStart,            //  InstanceTeardownStart
    wdfltInstanceTeardownComplete,         //  InstanceTeardownComplete

    NULL,                               //  GenerateFileName
    NULL,                               //  GenerateDestinationFileName
    NULL                                //  NormalizeNameComponent

};


NTSTATUS DriverEntry ( __in DRIVER_OBJECT *DriverObject,  __in UNICODE_STRING *RegistryPath )
{
    NTSTATUS status;

    WDFLT_DbgPrint ( LOG_INFO, ( "Enter DriverEntry." ) );


    status = FltRegisterFilter ( DriverObject,
                                 &FilterRegistration,
                                 &gFilterHandle );

    FLT_ASSERT ( NT_SUCCESS ( status ) );

    if ( NT_SUCCESS ( status ) )
    {

        //
        //  Start filtering i/o
        //

        status = FltStartFiltering ( gFilterHandle );

        if ( !NT_SUCCESS ( status ) )
        {

            FltUnregisterFilter ( gFilterHandle );
        }
    }




    WDFLT_DbgPrint ( LOG_INFO, ( "Exit DriverEntry, status=0x%08x.", status ) );
    return status;
}