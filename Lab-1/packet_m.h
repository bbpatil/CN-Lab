//
// Generated file, do not edit! Created by nedtool 5.2 from packet.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __PACKET_M_H
#define __PACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0502
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>packet.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet Packet
 * {
 *     int Id;
 *     string type_of_message;
 *     int src_addr;
 *     int dest_addr;
 * }
 * </pre>
 */
class Packet : public ::omnetpp::cPacket
{
  protected:
    int Id;
    ::omnetpp::opp_string type_of_message;
    int src_addr;
    int dest_addr;

  private:
    void copy(const Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Packet&);

  public:
    Packet(const char *name=nullptr, short kind=0);
    Packet(const Packet& other);
    virtual ~Packet();
    Packet& operator=(const Packet& other);
    virtual Packet *dup() const override {return new Packet(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getId() const;
    virtual void setId(int Id);
    virtual const char * getType_of_message() const;
    virtual void setType_of_message(const char * type_of_message);
    virtual int getSrc_addr() const;
    virtual void setSrc_addr(int src_addr);
    virtual int getDest_addr() const;
    virtual void setDest_addr(int dest_addr);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Packet& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Packet& obj) {obj.parsimUnpack(b);}


#endif // ifndef __PACKET_M_H

