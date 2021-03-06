// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <vkt/Copy.hpp>
#include <vkt/StructuredVolume.hpp>

#include <vkt/Copy.h>
#include <vkt/StructuredVolume.h>

#include "Copy_cuda.hpp"
#include "Copy_serial.hpp"
#include "macros.hpp"
#include "StructuredVolume_impl.hpp"

//-------------------------------------------------------------------------------------------------
// C++ API
//

namespace vkt
{
    Error Copy(StructuredVolume& dst, StructuredVolume& src)
    {
        VKT_CALL__(
            CopyRange,
            dst,
            src,
            { 0, 0, 0 },
            dst.getDims(),
            { 0, 0, 0 }
            );

        return NoError;
    }

    Error CopyRange(
            StructuredVolume& dst,
            StructuredVolume& src,
            int32_t firstX,
            int32_t firstY,
            int32_t firstZ,
            int32_t lastX,
            int32_t lastY,
            int32_t lastZ,
            int32_t dstOffsetX,
            int32_t dstOffsetY,
            int32_t dstOffsetZ
            )
    {
        VKT_CALL__(
            CopyRange,
            dst,
            src,
            { firstX, firstY, firstZ },
            { lastX, lastY, lastZ },
            { dstOffsetX, dstOffsetY, dstOffsetZ }
            );

        return NoError;
    }

    Error CopyRange(
            StructuredVolume& dst,
            StructuredVolume& src,
            Vec3i first,
            Vec3i last,
            Vec3i dstOffset
            )
    {
        VKT_CALL__(CopyRange, dst, src, first, last, dstOffset);

        return NoError;
    }

} // vkt

//-------------------------------------------------------------------------------------------------
// C API
//

vktError vktCopySV(vktStructuredVolume dst, vktStructuredVolume src)
{
    VKT_CALL__(
        CopyRange,
        dst->volume,
        src->volume,
        { 0, 0, 0 },
        dst->volume.getDims(),
        { 0, 0, 0 }
        );

    return vktNoError;
}

vktError vktCopyRangeSV(
        vktStructuredVolume dst,
        vktStructuredVolume src,
        int32_t firstX,
        int32_t firstY,
        int32_t firstZ,
        int32_t lastX,
        int32_t lastY,
        int32_t lastZ,
        int32_t dstOffsetX,
        int32_t dstOffsetY,
        int32_t dstOffsetZ
        )
{
    VKT_CALL__(
        CopyRange,
        dst->volume,
        src->volume,
        { firstX, firstY, firstZ },
        { lastX, lastY, lastZ },
        { dstOffsetX, dstOffsetY, dstOffsetZ }
        );

    return vktNoError;
}
