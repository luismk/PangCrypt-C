# PangCrypt-C

PangCrypt-C is an implementation of the PangYa transport cryptography. It is a C++ port of the Go pangbox pangcrypt library.

## MiniLzo

A port of the LZO library is embedded in the PangCrypt solution. It is based partly on a port of MiniLzo by Frank Razenberg and the original MiniLzo library by Markus Oberhumer. It is licensed under GPLv2+.

The remainder of PangCrypt-C is licensed under the ISC license, which is compatible with the GPLv2+ license.

## TODO

This repository is a WIP.

  - [x] Implement basic encoding and decoding routines.
  - [x] Implement Console for testing.
  - [x] Methods imported for use in other applications.
  - [x] Works with Reina's Server.
  - [ ] Re-implement LZO from scratch, with Streams.
  - [ ] Rewrite encoding/decoding to use Streams.

The Console is for testing and might be separated into its own project. It is not covered under automated testing and has limited functionality (it does, however, actually work.)
