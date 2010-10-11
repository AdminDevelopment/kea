// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#ifndef __RECURSOR_H
#define __RECURSOR_H 1

#include <string>

#include <cc/data.h>
#include <config/ccsession.h>

#include <asiolink/asiolink.h>

class RecursorImpl;

class Recursor {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    Recursor(const Recursor& source);
    Recursor& operator=(const Recursor& source);
public:
    /// The constructor.
    ///
    /// \param forward The address of the name server to which requests
    /// should be forwarded.  (In the future, when the server is running
    /// in forwarding mode, the forward nameserver addresses will be set
    /// via the config channel instaed.)
    Recursor(const char& forward);
    ~Recursor();
    //@}

    /// \brief Process an incoming DNS message, then signal 'server' to resume 
    void processMessage(const asiolink::IOMessage& io_message,
                        isc::dns::MessagePtr message,
                        isc::dns::OutputBufferPtr buffer,
                        asiolink::DNSServer* server);

    // \brief Set and get verbose mode
    void setVerbose(bool on);
    bool getVerbose() const;

    /// \brief Set and get the config session
    isc::config::ModuleCCSession* getConfigSession() const;
    void setConfigSession(isc::config::ModuleCCSession* config_session);

    /// \brief Handle commands from the config session
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);

    /// \brief Assign an ASIO IO Service queue to this Recursor object
    void setIOService(asiolink::IOService& ios);

    /// \brief Return this object's ASIO IO Service queue
    asiolink::IOService& getIOService() const { return (*io_); }

    /// \brief Return pointer to the DNS Lookup callback function
    asiolink::DNSLookup* getDNSLookupProvider() { return (dns_lookup_); }

    /// \brief Return pointer to the DNS Answer callback function
    asiolink::DNSAnswer* getDNSAnswerProvider() { return (dns_answer_); }

    /// \brief Return pointer to the Checkin callback function
    asiolink::SimpleCallback* getCheckinProvider() { return (checkin_); }

private:
    RecursorImpl* impl_;
    asiolink::IOService* io_;
    asiolink::SimpleCallback* checkin_;
    asiolink::DNSLookup* dns_lookup_;
    asiolink::DNSAnswer* dns_answer_;
};

#endif // __RECURSOR_H

// Local Variables: 
// mode: c++
// End: 
