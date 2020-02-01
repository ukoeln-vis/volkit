// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#include <vkt/linalg.hpp>
#include <vkt/StructuredVolume.hpp>

namespace vkt
{
    static void CopyRange_serial(
            StructuredVolume& dst,
            StructuredVolume& src,
            Vec3i first,
            Vec3i last,
            Vec3i dstOffset
            )
    {
        if (dst.getBytesPerVoxel() == src.getBytesPerVoxel()
          && dst.getVoxelMapping() == src.getVoxelMapping())
        {
            uint8_t voxel[StructuredVolume::GetMaxBytesPerVoxel()];

            for (int32_t z = first.z; z != last.z; ++z)
            {
                for (int32_t y = first.y; y != last.y; ++y)
                {
                    for (int32_t x = first.x; x != last.x; ++x)
                    {
                        for (uint16_t i = 0; i < dst.getBytesPerVoxel(); ++i)
                        {
                            Vec3i dims = src.getDims();

                            int32_t srcX = clamp(x, 0, dims.x - 1);
                            int32_t srcY = clamp(y, 0, dims.y - 1);
                            int32_t srcZ = clamp(z, 0, dims.z - 1);

                            int32_t dstX = x - first.x + dstOffset.x;
                            int32_t dstY = y - first.y + dstOffset.y;
                            int32_t dstZ = z - first.z + dstOffset.z;

                            src.getVoxel(srcX, srcY, srcZ, voxel);
                            dst.setVoxel(dstX, dstY, dstZ, voxel);
                        }
                    }
                }
            }
        }
        else
        {
            for (int32_t z = first.z; z != last.z; ++z)
            {
                for (int32_t y = first.y; y != last.y; ++y)
                {
                    for (int32_t x = first.x; x != last.x; ++x)
                    {
                        for (uint16_t i = 0; i < dst.getBytesPerVoxel(); ++i)
                        {
                            Vec3i dims = src.getDims();

                            int32_t srcX = clamp(x, 0, dims.x - 1);
                            int32_t srcY = clamp(y, 0, dims.y - 1);
                            int32_t srcZ = clamp(z, 0, dims.z - 1);

                            int32_t dstX = x - first.x + dstOffset.x;
                            int32_t dstY = y - first.y + dstOffset.y;
                            int32_t dstZ = z - first.z + dstOffset.z;

                            float val = 0.f;
                            src.getValue(srcX, srcY, srcZ, val);
                            dst.setValue(dstX, dstY, dstZ, val);
                        }
                    }
                }
            }
        }
    }
} // vkt
