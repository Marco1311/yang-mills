#ifndef GAUGE_CONF_H
#define GAUGE_CONF_H

#include"macro.h"

#include<complex.h>
#ifdef HASH_MODE
  #include<openssl/md5.h>
#endif
#include<stdio.h>

#include"gparam.h"
#include"geometry.h"
#include"su2.h"
#include"sun.h"
#include"tens_prod.h"
#include"u1.h"


typedef struct Gauge_Conf {
  long update_index;

  GAUGE_GROUP **lattice;       // [volume][4]
  GAUGE_GROUP ***clover_array; // [volume][4][4]

  // for computing the polyakov loop correlator with multilevel
  TensProd **ml_polycorr_ris;    // [NLEVELS][space_vol]
  TensProd **ml_polycorr_tmp;    // [NLEVELS][space_vol]
  GAUGE_GROUP *loc_poly;         // [space_vol] auxilliary vector to be used in the multilevel

  // for the disconnected correlator for string width
  TensProd **ml_polyplaq_ris;   // [NLEVELS][space_vol]
  TensProd **ml_polyplaq_tmp;   // [NLEVELS][space_vol]
  double complex *loc_plaq;     // [space_vol] auxilliary vector to be used in the multilevel

  // for the connected correlator for string width
  TensProd **ml_polyplaqconn_ris;   // [NLEVELS][space_vol]
  TensProd **ml_polyplaqconn_tmp;   // [NLEVELS][space_vol]
  GAUGE_GROUP *loc_polyplaqconn;    // [space_vol] auxilliary vector to be used in the multilevel
  } Gauge_Conf;


// in gauge_conf_def.c
void init_gauge_conf(Gauge_Conf *GC,
                     GParam const * const param);
void read_gauge_conf(Gauge_Conf *GC,
                     GParam const * const param);
void free_gauge_conf(Gauge_Conf *GC,
                    GParam const * const param);
void write_conf_on_file_with_name(Gauge_Conf const * const GC,
                                  GParam const * const param,
                                  char const * const namefile);
void write_conf_on_file(Gauge_Conf const * const GC,
                        GParam const * const param);
void write_conf_on_file_back(Gauge_Conf const * const GC,
                             GParam const * const param);
void init_gauge_conf_from_gauge_conf(Gauge_Conf *GC,
                                     Gauge_Conf const * const GC2,
                                     GParam const * const param);
void compute_md5sum(char *res,        // the lenght is 2*MD5_DIGEST_LENGTH
                    Gauge_Conf const * const GC,
                    GParam const * const param);

void alloc_polycorr_stuff(Gauge_Conf *GC,
                           GParam const * const param);
void free_polycorr_stuff(Gauge_Conf *GC);
void write_polycorr_on_file(Gauge_Conf const * const GC,
                            GParam const * const param,
                            int tstart,
                            int iteration);
void read_polycorr_from_file(Gauge_Conf const * const GC,
                             GParam const * const param,
                             int *tstart,
                             int *iteration);
void compute_md5sum_polycorr(char *res,        // the lenght is 2*MD5_DIGEST_LENGTH
                             Gauge_Conf const * const GC,
                             GParam const * const param);

void alloc_tube_disc_stuff(Gauge_Conf *GC,
                                GParam const * const param);
void free_tube_disc_stuff(Gauge_Conf *GC);
void write_polycorr_and_polyplaq_on_file(Gauge_Conf const * const GC,
                                         GParam const * const param,
                                         int tstart,
                                         int iteration);
void read_polycorr_and_polyplaq_from_file(Gauge_Conf const * const GC,
                                          GParam const * const param,
                                          int *tstart,
                                          int *iteration);
void compute_md5sum_polycorr_and_polyplaq(char *res,        // the lenght is 2*MD5_DIGEST_LENGTH
                                          Gauge_Conf const * const GC,
                                          GParam const * const param);

void alloc_tube_conn_stuff(Gauge_Conf *GC,
                           GParam const * const param);
void free_tube_conn_stuff(Gauge_Conf *GC);
void alloc_clover_array(Gauge_Conf *GC,
                        GParam const * const param);
void end_clover_array(Gauge_Conf *GC,
                      GParam const * const param);


// in gauge_conf_meas.c
double plaquettep(Gauge_Conf const * const GC,
                  Geometry const * const geo,
                  GParam const * const param,
                  long r,
                  int i,
                  int j);
double complex plaquettep_complex(Gauge_Conf const * const GC,
                                  Geometry const * const geo,
                                  GParam const * const param,
                                  long r,
                                  int i,
                                  int j);
void plaquettep_matrix(Gauge_Conf const * const GC,
                       Geometry const * const geo,
                       GParam const * const param,
                       long r,
                       int i,
                       int j,
                       GAUGE_GROUP *matrix);
void clover(Gauge_Conf const * const GC,
            Geometry const * const geo,
            GParam const * const param,
            long r,
            int i,
            int j,
            GAUGE_GROUP *M);
void plaquette(Gauge_Conf const * const GC,
               Geometry const * const geo,
               GParam const * const param,
               double *plaqs,
               double *plaqt);
void clover_disc_energy(Gauge_Conf const * const GC,
                        Geometry const * const geo,
                        GParam const * const param,
                        double *energy);
void polyakov(Gauge_Conf const * const GC,
              Geometry const * const geo,
              GParam const * const param,
              double *repoly,
              double *impoly);
double topcharge(Gauge_Conf const * const GC,
                 Geometry const * const geo,
                 GParam const * const param);
void perform_measures_localobs(Gauge_Conf const * const GC,
                               Geometry const * const geo,
                               GParam const * const param,
                               FILE *datafilep);

void optimize_multihit_polycorr(Gauge_Conf *GC,
                       Geometry const * const geo,
                       GParam const * const param,
                       FILE *datafilep);
void optimize_multilevel_polycorr(Gauge_Conf *GC,
                                  Geometry const * const geo,
                                  GParam const * const param,
                                  FILE *datafilep);
void perform_measures_polycorr(Gauge_Conf * GC,
                                Geometry const * const geo,
                                GParam const * const param,
                                FILE *datafilep);
void optimize_multilevel_polycorr_long(Gauge_Conf *GC,
                                       GParam const * const param,
                                       FILE *datafilep);
void perform_measures_potlycorr_long(Gauge_Conf * GC,
                                     GParam const * const param,
                                     FILE *datafilep);
void perform_measures_tube_disc(Gauge_Conf *GC,
                                Geometry const * const geo,
                                GParam const * const param,
                                FILE *datafilep);
void perform_measures_tube_disc_long(Gauge_Conf *GC,
                                     GParam const * const param,
                                     FILE *datafilep);
void perform_measures_tube_conn(Gauge_Conf *GC,
                                Geometry const * const geo,
                                GParam const * const param,
                                FILE *datafilep);


// in gauge_conf_multilevel.c
void multihit(Gauge_Conf const * const GC,
              Geometry const * const geo,
              GParam const * const param,
              long r,
              int dir,
              int num_hit,
              GAUGE_GROUP *G);
void compute_local_poly(Gauge_Conf *GC,
                        Geometry const * const geo,
                        GParam const * const param,
                        int t_start,
                        int dt);
void slice_compute_clovers(Gauge_Conf const * const GC,
                           Geometry const * const geo,
                           GParam const * const param,
                           int dir,
                           int t_start,
                           int dt);
void slice_single_update(Gauge_Conf *GC,
                         Geometry const * const geo,
                         GParam const * const param,
                         int t_start,
                         int dt);
void multilevel_polycorr(Gauge_Conf *GC,
                          Geometry const * const geo,
                          GParam const * const param,
                          int t_start,
                          int dt);
void multilevel_potlycorr_long(Gauge_Conf * GC,
                               Geometry const * const geo,
                               GParam const * const param,
                               int t_start,
                               int dt,
                               int iteration);
void compute_plaq_on_slice1(Gauge_Conf *GC,
                            Geometry const * const geo,
                            GParam const * const param);
void multilevel_tube_disc(Gauge_Conf *GC,
                          Geometry const * const geo,
                          GParam const * const param,
                          int t_start,
                          int dt);
void multilevel_tube_disc_long(Gauge_Conf *GC,
                               Geometry const * const geo,
                               GParam const * const param,
                               int t_start,
                               int dt,
                               int iteration);
void compute_poly_polyplaq_and_polyplaqconn_on_slice1(Gauge_Conf *GC,
                                                      Geometry const * const geo,
                                                      GParam const * const param);
void multilevel_tube_conn(Gauge_Conf * GC,
                          Geometry const * const geo,
                          GParam const * const param,
                          int t_start,
                          int dt);


// in gauge_conf_upd.c
void calcstaples_wilson(Gauge_Conf const * const GC,
                        Geometry const * const geo,
                        GParam const * const gparam,
                        long r,
                        int i,
                        GAUGE_GROUP *M);
void calcstaples_tracedef(Gauge_Conf const * const GC,
                          Geometry const * const geo,
                          GParam const * const param,
                          long r,
                          int i,
                          GAUGE_GROUP * M);
void compute_clovers(Gauge_Conf const * const GC,
                     Geometry const * const geo,
                     GParam const * const param,
                     int direction);
void calcstaples_with_topo(Gauge_Conf const * const GC,
                           Geometry const * const geo,
                           GParam const * const param,
                           long r,
                           int i,
                           GAUGE_GROUP *M);
void heatbath(Gauge_Conf * GC,
              Geometry const * const geo,
              GParam const * const param,
              long r,
              int i);
void overrelaxation(Gauge_Conf * GC,
                    Geometry const * const geo,
                    GParam const * const param,
                    long r,
                    int i);
int metropolis(Gauge_Conf *GC,
               Geometry const * const geo,
               GParam const * const param,
               long r,
               int i);
int metropolis_with_tracedef(Gauge_Conf *GC,
                             Geometry const * const geo,
                             GParam const * const param,
                             long r,
                             int i);
void update(Gauge_Conf *GC,
            Geometry const * const geo,
            GParam const * const param);
void update_with_trace_def(Gauge_Conf *GC,
                           Geometry const * const geo,
                           GParam const * const param,
                           double *acc);
void cooling(Gauge_Conf *GC,
             Geometry const * const geo,
             GParam const * const param,
             int n);
void gradflow_RKstep(Gauge_Conf *GC,
                     Gauge_Conf *helper1,
                     Gauge_Conf *helper2,
                     Geometry const * const geo,
                     GParam const *const param,
                     double dt);
void ape_smearing(Gauge_Conf *GC,
                  Geometry const * const geo,
                  GParam const *const param,
                  double alpha,
                  int n);

#endif
