/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_DEFAULT_BT_PROGRESS_INFO_FILE_H_
#define _D_DEFAULT_BT_PROGRESS_INFO_FILE_H_

#include "BtProgressInfoFile.h"

namespace aria2 {

class DownloadContext;
class PieceStorage;
class PeerStorage;
class BtRuntime;
class Logger;
class Option;

class DefaultBtProgressInfoFile : public BtProgressInfoFile {
private:
  SharedHandle<DownloadContext> _dctx;
  SharedHandle<PieceStorage> _pieceStorage;
#ifdef ENABLE_BITTORRENT
  SharedHandle<PeerStorage> _peerStorage;
  SharedHandle<BtRuntime> _btRuntime;
#endif // ENABLE_BITTORRENT
  const Option* _option;
  Logger* _logger;
  std::string _filename;

  bool isTorrentDownload();

  static const std::string V0000;
  static const std::string V0001;
public:
  DefaultBtProgressInfoFile(const SharedHandle<DownloadContext>& btContext,
			    const SharedHandle<PieceStorage>& pieceStorage,
			    const Option* option);

  virtual ~DefaultBtProgressInfoFile();

  virtual std::string getFilename() { return _filename; }
  
  virtual bool exists();

  virtual void save();

  virtual void load();

  virtual void removeFile();

  // re-set filename using current _dctx.
  virtual void updateFilename();

#ifdef ENABLE_BITTORRENT
  // for torrents
  void setPeerStorage(const SharedHandle<PeerStorage>& peerStorage);

  void setBtRuntime(const SharedHandle<BtRuntime>& btRuntime);
#endif // ENABLE_BITTORRENT
};

} // namespace aria2

#endif // _D_DEFAULT_BT_PROGRESS_INFO_FILE_H_
