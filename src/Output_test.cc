#include <stdlib.h>

#include "Output.h"

void
Output::text (FILE* out, Tracert *results, Options* opts) {
  fprintf(out, "traceroute [(%s:%d) -> (%s:%d)], protocol %s, algo %s\n",
			opts->src_addr, opts->src_port,
			opts->dst_addr, opts->dst_port,
			opts->protocol, opts->algo);
  for (int i = results->getMinTTL(); i <= results->getMaxTTL(); i++) {
    //if (i < 10) fprintf(out, " %d ", i);
    //else fprintf(out, "%d ", i);
    fprintf(out, "%2d ", i);
    
    //int index = -1;
    //for (int j = 0; j < opts->max_try; j++) {
    //  if (results->getHopInfo(i, j)->getHostAddress() != NULL) {
    //    index = j;
    //    break;
    //  }
    //}

    const TimedProbe* last_tprobe = NULL;
    for (int j = 0; j < opts->max_try; j++) {
      const TimedProbe* tprobe = results->getHopInfo(i, j);
      //bool different_address = false;
      //if (index == j) show_address = true;
      //if (index != j && tprobe != NULL && last_tprobe != NULL
      //  && tprobe->host_address_raw != last_tprobe->host_address_raw)
      //  show_address = true;

      // We received a valid reply
      if (tprobe->arrival_time != 0) {
        // The current address is different : print it
        // Check if the current and previous addresses are the same
        if (last_tprobe == NULL 
          || (tprobe->host_address_raw != last_tprobe->host_address_raw)) {
          if (opts->resolve_hostname)
            fprintf(out," %s (%s) ", tprobe->getHostName(), tprobe->getHostAddress());
          else
            fprintf(out," %s ", tprobe->getHostAddress());
        }
        
        // Print the arrival time
        fprintf(out, " %04.03f ms ", ((float)tprobe->getRTT()) / 1000.0);
        
        switch (tprobe->reply_type)
        {
          case Reply::HOST_UNREACHABLE:
            fprintf(out, "!H ");
            break;
          case Reply::NETWORK_UNREACHABLE:
            fprintf(out, "!N ");
            break;
          case Reply::SOURCE_QUENCH:
            fprintf(out, "!Q ");
            break;
          default:
            break;
        }
        
        // Print the probe TTL if it has a strange value
        if (tprobe->reply_ttl != 1 && tprobe->reply_ttl != -1)
          fprintf(out, "!T%d ", tprobe->reply_ttl);

        // Print the IP ID of the packet returned by the router (or target)
        if (opts->display_ipid)
          fprintf(out, "{%d} ", tprobe->ip_id);

        // Print the original TTL
        if (opts->display_ttl)
          fprintf(out, "[%d] ", tprobe->fabien_ttl);

        // Update only if tprobe is valid
        last_tprobe = tprobe;
      } else
        // No valid reply : just print a star
        fprintf(out, " *");
       
      //if (show_address && opts->resolve_hostname) {
        // check if we have received a reply
        //if (tprobe->arrival_time != 0)
          //fprintf(out," %s (%s) ",tprobe->getHostName(),tprobe->getHostAddress());
      //}

      //if (show_address && !opts->resolve_hostname)
        //fprintf(out," %s (%s) ", tprobe->getHostName(), tprobe->getHostAddress());

      //if (tprobe == NULL || tprobe->arrival_time == 0) fprintf(out, " *");

      //if (tprobe != NULL && tprobe->arrival_time != 0)
        //fprintf(out, " %04.03f ", ((float)tprobe->getRTT()) / 1000.0);

//       if (tprobe->arrival_time != 0) {
//         switch (tprobe->reply_type)
//         {
//           case Reply::HOST_UNREACHABLE:
//             fprintf(out, "!H ");
//             break;
//           case Reply::NETWORK_UNREACHABLE:
//             fprintf(out, "!N ");
//             break;
//           case Reply::SOURCE_QUENCH:
//             fprintf(out, "!Q ");
//             break;
//           default:
//             break;
//         }
//       }

      // Print the returned TTL (sticky nodes/targets should return weird TTLs)
      // XXX show only if interesting  TTLs !!
//      if (tprobe->arrival_time != 0 
//        && tprobe->reply_ttl != 1 && tprobe->reply_ttl != -1)
//        fprintf(out, "!T%d ", tprobe->reply_ttl);

      // Print the IP ID of the packet returned by the router (or target)
      // XXX show only if user requested it !!!
//       if (&& tprobe->arrival_time != 0 && opts->display_ipid)
//         fprintf(out, "{%d} ", tprobe->ip_id);

//       if (tprobe != NULL && tprobe->arrival_time != 0 && opts->display_ttl)
//         fprintf(out, "[%d] ", tprobe->fabien_ttl);
        
      // Update only if tprobe is valid
//       if (tprobe->arrival_time !=0)
//         last_tprobe = tprobe;
    }
    fprintf(stdout, "\n");

    // Print a second line if there are MPLS informations
    //

    last_tprobe = NULL;
    bool new_line = false;

    for (int j = 0; j < opts->max_try; j++) {
      const TimedProbe* tprobe = results->getHopInfo(i, j);
      bool show_stack = false;

      if (tprobe != NULL && tprobe->mpls_stack != NULL
        && last_tprobe != NULL){
        if (MPLSHeader::compareStacks(tprobe->mpls_stack, tprobe->nbrLabels,
            last_tprobe->mpls_stack, last_tprobe->nbrLabels) != 0) {
            fprintf(stderr, ", ");
            show_stack = true;
        }
      }
      else if (tprobe != NULL && tprobe->mpls_stack != NULL) {
	  	if(!opts->display_json)
        	fprintf(stderr, "   MPLS Label ");
        show_stack = true;
        last_tprobe = tprobe;
      }

      if (show_stack) {
	  	if(!opts->display_json)
	  	{
        	fprintf(stdout, "%d TTL=%d", tprobe->mpls_stack[0], tprobe->mpls_ttl);

        	for (int j = 1; j < tprobe->nbrLabels; j++)
           		fprintf(stdout, " | %d", tprobe->mpls_stack[j]);
	  	
        	new_line = true;
	  	}
      }
      last_tprobe = tprobe;
    }
    if (new_line) fprintf(stdout, "\n");
  }
}

