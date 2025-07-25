// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "FloppyFile.h"

namespace vamiga {

class IMGFile : public FloppyFile {
    
public:

    static constexpr isize IMGSIZE_35_DD = 737280;  // 720 KB PC disk
    
    static bool isCompatible(const fs::path &path);
    static bool isCompatible(const u8 *buf, isize len);
    static bool isCompatible(const Buffer<u8> &buffer);

    
    //
    // Initializing
    //
    
public:
    
    using AnyFile::init;
    
    IMGFile(const fs::path &path) throws { init(path); }
    // IMGFile(const fs::path &path, std::istream &stream) throws { init(path, stream); }
    IMGFile(const u8 *buf, isize len) throws { init(buf, len); }
    IMGFile(Diameter dia, Density den) throws { init(dia, den); }
    IMGFile(class FloppyDisk &disk) throws { init(disk); }
    IMGFile(class FloppyDrive &drive) throws { init(drive); }

private:
    
    void init(Diameter dia, Density den) throws;
    void init(class FloppyDisk &disk) throws;
    void init(FloppyDrive &drive) throws;


    //
    // Methods from CoreObject
    //
    
public:
    
    const char *objectName() const override { return "IMG"; }
    
    
    //
    // Methods from AnyFile
    //

    bool isCompatiblePath(const fs::path &path) const override { return isCompatible(path); }
    bool isCompatibleBuffer(const u8 *buf, isize len) const override { return isCompatible(buf, len); }
    FileType type() const override { return FileType::IMG; }
    
    
    //
    // Methods from DiskFile
    //

    isize numCyls() const override;
    isize numHeads() const override;
    isize numSectors() const override;
    
    
    //
    // Methods from FloppyFile
    //

    FSFormat getDos() const override { return FSFormat::NODOS; }
    void setDos(FSFormat dos) override { };
    Diameter getDiameter() const override { return Diameter::INCH_35; }
    Density getDensity() const override { return Density::DD; }
    void encodeDisk(class FloppyDisk &disk) const throws override;
    void decodeDisk(const class FloppyDisk &disk) throws override;

private:
    
    void encodeTrack(class FloppyDisk &disk, Track t) const throws;
    void encodeSector(class FloppyDisk &disk, Track t, Sector s) const throws;

    void decodeTrack(const class FloppyDisk &disk, Track t) throws;
    void decodeSector(u8 *dst, const u8 *src);
};

}
