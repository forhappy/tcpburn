#ifndef GRYPHON_INCLUDED
#define GRYPHON_INCLUDED 

#define LOCALHOST (inet_addr("127.0.0.1"))

typedef struct {
    char file[256];
} tc_pcap_file;

typedef struct {
    /* online ip from the client perspective */
    uint32_t      online_ip;
    uint32_t      target_ip;
    uint16_t      online_port;
    uint16_t      target_port;
    unsigned char src_mac[ETHER_ADDR_LEN];
    unsigned char dst_mac[ETHER_ADDR_LEN];
} ip_port_pair_mapping_t;


typedef struct {
    int                      num;
    ip_port_pair_mapping_t **mappings;
} ip_port_pair_mappings_t;

typedef struct real_ip_addr_s {
    int           num;
    int           active_num;
    short         active[MAX_REAL_SERVERS];
    uint32_t      ips[MAX_REAL_SERVERS];
    uint16_t      ports[MAX_REAL_SERVERS];
    connections_t connections[MAX_REAL_SERVERS];
} real_ip_addr_t;

typedef struct xcopy_clt_settings {
    unsigned int  mtu:16;               /* MTU sent to backend */
    unsigned int  mss:16;               /* MSS sent to backend */
    unsigned int  par_connections:8;    /* parallel connections */
    unsigned int  client_mode:3;     
    unsigned int  do_daemonize:1;       /* daemon flag */
    unsigned int  percentage:7;         /* percentage of the full flow that 
                                           will be tranfered to the backend */
    unsigned int  session_timeout:16;   /* max value for session timeout.
                                           If reaching this value, the session
                                           will be removed */
    unsigned int  session_keepalive_timeout:16;  
    unsigned int  target_localhost:1;

    char         *raw_transfer;         /* online_ip online_port target_ip
                                           target_port string */

    char         *pid_file;             /* pid file */
    char         *log_path;             /* error log path */
    char         *raw_clt_ips;              
    int           valid_ip_num;              
    uint32_t      valid_ips[M_CLIENT_IP_NUM];              
    int           users;
    int           throughput_factor;   
    char         *raw_pcap_files;          
    char         *filter;          
    tc_pcap_file  pcap_files[MAX_PCAP_FILES]; 
    int           num_pcap_files;       
    int           conn_init_sp_fact;
    long          pcap_time;
    pcap_t       *pcap;
    uint64_t      interval;             /* accelerated times */
#if (GRYPHON_PCAP_SEND)
    char         *output_if_name;
#endif
    uint16_t      rand_port_shifted;   /* random port shifted */
    uint16_t      srv_port;            /* server listening port */
    char         *raw_rs_list;         /* raw real server list */
    real_ip_addr_t  real_servers;      /* the intercept servers running intercept */
    ip_port_pair_mappings_t transfer;  /* transfered online_ip online_port
                                           target_ip target_port */
    int           multiplex_io;
    int           sig;  
    uint64_t      tries;  
} xcopy_clt_settings;


extern int tc_raw_socket_out;
extern tc_event_loop_t event_loop;
extern xcopy_clt_settings clt_settings;

#include <tc_util.h>

#include <tc_manager.h>
#include <tc_user.h>
#include <tc_message_module.h>
#include <tc_packets_module.h>

#endif /* GRYPHON_INCLUDED */
