#ifndef _EVERNOTE_SYNC_HH_
#define _EVERNOTE_SYNC_HH_

#include <libevernote/evernote.hh>
#include "sync.hh"
#include "notify.hh"

class EvernoteSyncClient : public SyncClient {
	private:
		std::string authToken;
    std::string server;
    bool authTokenQueryDone;

    long updateSequenceNumber;
    bool updateSequenceNumberQueryDone;

    evernote::NoteStore* noteStore;

    evernote::UserStore* userStore;

		static int checkAuthTokenCallback (void* esc, int argc, char** argv, char** azColName);
    static int checkUpdateSequenceNumberCallback (void* esc, int argc, char** argv, char** azColName);
    static int checkEvernoteServerCallback (void*, int, char**, char**);
public:
	EvernoteSyncClient (Notify* app) {
		this->app = app;
	}
	int sync (int);
	static void firstStageComplete(WebKitWebView  *web_view,
               WebKitWebFrame *web_frame,
               gpointer        user_data); 

	static void secondStageComplete(WebKitWebView  *web_view,
               WebKitWebFrame *web_frame,
               gpointer        user_data); 
	static void thirdStageComplete(WebKitWebView  *web_view,
               WebKitWebFrame *web_frame,
               gpointer        user_data); 
	static void fourthStageComplete(WebKitWebView  *web_view,
               WebKitWebFrame *web_frame,
               gpointer        user_data); 

  void syncNotes (long updateSequenceNumber);
  void syncNotebooks (long updateSequenceNumber);

  int getNoteStore ();
  int getUserStore (int);

  evernote::SyncState* getSyncState ();
  evernote::SyncChunk* getFilteredSyncChunk (int afterUSN,
      int maxEntries, evernote::SyncChunkFilter* filter);
  void updateUpdateSequenceNumInDatabase (long);


  void actualSync (std::string, long usn, int syncStateUSN);
  void actualSync (std::string);
  void saveResource (evernote::Resource*);


  evernote::OAuthManager* oAuthManager;

	void* handle; // handle to the dll file.
	EvernoteWebViewBox* ewvb;
	int signalHandlerId;	
	void getNoteDataObject (evernote::Note* note);
};

#endif
