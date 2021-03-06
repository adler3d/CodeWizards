#define _ALLOW_KEYWORD_MACROS
#if(!defined(_DEBUG)&&!defined(Adler))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma warning(push,1)
#include <cstring>
#endif
#ifndef NOMINMAX
  #define NOMINMAX  
#endif
#define private public
#define protected public
#include "MyStrategy.h"
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
using std::vector;
using std::string;
//#undef Adler
#ifdef Adler
  #include <Windows.h>
  #include <fstream>
  inline string IToS(const int&val){char c[16];_itoa_s(val,c,10);return string(c);}
  inline string FToS(const double&val){char c[64];if(abs(val)>1e9){_snprintf_s(c,32,32,"%e",val);}else{sprintf_s(c,"%f",val);}return string(c);}
  inline string FToS2(const double&val){char c[64];if(abs(val)>1e9){_snprintf_s(c,32,32,"%e",val);}else{sprintf_s(c,"%.2f",val);}return string(c);}
  static bool IsKeyDown(int vKey){int i=GetAsyncKeyState(vKey);return i<0;}
  #define KB_CODE(){auto mwta=game.getWizardMaxTurnAngle();if(IsKeyDown('Q'))move.setTurn(-mwta);if(IsKeyDown('E'))move.setTurn(+mwta);if(IsKeyDown('W'))move.setSpeed(+100);if(IsKeyDown('S'))move.setSpeed(-100);if(IsKeyDown('D'))move.setStrafeSpeed(+100);if(IsKeyDown('A'))move.setStrafeSpeed(-100);}
  static bool file_put_contents(const string&FN,const string&mem)
  {
    using namespace std;
    fstream f;
    f.open(FN.c_str(),ios::out|ios::binary);
    if(!f)return false;
    if(!mem.empty())f.write(&mem[0],mem.size());
    f.close();
    return true;
  };
#else
  void KB_CODE(){}
  static bool file_put_contents(const string&FN,const string&mem){return true;}
#endif

#define QapAssert(COND)if(!(COND))__debugbreak();

#define PRO_FUNCGEN_GETP_BY_FIELD(rettype,getp,arr,field_type,field)\
  rettype*getp(field_type value)\
  {\
    rettype*p=nullptr;\
    for(int i=0;i<arr.size();i++){\
      auto&ex=arr[i];\
      if(ex.field!=value)continue;\
      QapAssert(!p);\
      p=&ex;\
    }\
    return p;\
  }

#define PRO_FUNCGEN_ADD_UNIQUE_OBJ_BY_FIELD_V2(rettype,adduni,arr,field_type,field)\
  rettype*adduni(field_type value)\
  {\
    rettype*p=nullptr;\
    for(int i=0;i<arr.size();i++){\
      auto&ex=arr[i];\
      if(ex.field!=value)continue;\
      QapAssert(!p);\
      p=&ex;\
    }\
    if(!p){p=&qap_add_back(arr);p->field=value;}\
    return p;\
  }


template<typename TYPE,size_t COUNT>inline size_t lenof(TYPE(&)[COUNT]){return COUNT;}
template<class TYPE,class FUNC>
int qap_minval_id_for_vec(vector<TYPE>&arr,FUNC func){
  if(arr.empty())return -1;                         
  int id=0;auto val=func(arr[0],0); 
  for(int i=1;i<arr.size();i++){                    
    auto&ex=arr[i];                                 
    auto tmp=func(ex,i);                  
    if(tmp>=val)continue;               
    val=tmp;id=i;                 
  }                                                 
  return id;
}
template<class TYPE,class FUNC>
int qap_minval_id_for_vec(const vector<TYPE>&arr,FUNC func){
  if(arr.empty())return -1;                         
  int id=0;auto val=func(arr[0],0); 
  for(int i=1;i<arr.size();i++){                    
    auto&ex=arr[i];                                 
    auto tmp=func(ex,i);                  
    if(tmp>=val)continue;               
    val=tmp;id=i;                 
  }                                                 
  return id;
}

template<class TYPE>int qap_includes(const vector<TYPE>&arr,const TYPE&value){for(int i=0;i<arr.size();i++){if(arr[i]==value)return true;}return false;}

#define QAP_MINVAL_ID_OF_VEC(arr,code)qap_minval_id_for_vec(arr,[&](decltype(arr[0])&ex,int i){return code;})

template<class TYPE,class FUNC>void qap_foreach(vector<TYPE>&arr,FUNC func){for(int i=0;i<arr.size();i++)func(arr[i],i);}
template<class TYPE,class FUNC>void qap_foreach(const vector<TYPE>&arr,FUNC func){for(int i=0;i<arr.size();i++)func(arr[i],i);}
#define QAP_FOREACH(arr,code)qap_foreach(arr,[&](decltype(arr[0])&ex,int i){code;})

template<class TYPE,class FUNC>void clean_if(vector<TYPE>&Arr,FUNC&Pred){int last=0;for(int i=0;i<Arr.size();i++){auto&ex=Arr[i];if(Pred(ex))continue;if(last!=i){auto&ax=Arr[last];ax=std::move(ex);}last++;}if(last==Arr.size())return;Arr.resize(last);}
template<class TYPE,class FUNC>void clean_if(vector<TYPE>&Arr,const FUNC&Pred){int last=0;for(int i=0;i<Arr.size();i++){auto&ex=Arr[i];if(Pred(ex))continue;if(last!=i){auto&ax=Arr[last];ax=std::move(ex);}last++;}if(last==Arr.size())return;Arr.resize(last);}
template<class TYPE,class FUNC>void clean_if(vector<TYPE>&Arr,FUNC&&Pred){int last=0;for(int i=0;i<Arr.size();i++){auto&ex=Arr[i];if(Pred(ex))continue;if(last!=i){auto&ax=Arr[last];ax=std::move(ex);}last++;}if(last==Arr.size())return;Arr.resize(last);}

template<class TYPE>static TYPE&qap_add_back(vector<TYPE>&arr){arr.resize(arr.size()+1);return arr.back();}
template<typename TYPE>TYPE Sign(TYPE value){return (value>0)?TYPE(+1):TYPE(value<0?-1:0);}

typedef double real;const real Pi=3.14159265;const real Pi2=Pi*2;const real PiD2=Pi/2;const real PiD4=Pi/4;
template<class TYPE>inline TYPE Clamp(const TYPE&v,const TYPE&a,const TYPE&b){return std::max(a,std::min(v, b));}
template<typename TYPE>inline TYPE Lerp(const TYPE&A,const TYPE&B,const real&v){return A+(B-A)*v;}
class vec2d{
public:
  real x;real y;
  vec2d():x(0.0),y(0.0) {}
  vec2d(const real&x,const real&y):x(x),y(y) {}
  vec2d(const vec2d&v):x(v.x),y(v.y) {}
public:
  vec2d&operator=(const vec2d&v){x=v.x;y=v.y;return *this;}
  vec2d operator+()const{return *this;}
  vec2d operator-()const{return vec2d(-x,-y);}
  vec2d&operator+=(const vec2d&v){x+=v.x;y +=v.y;return *this;}
  vec2d&operator-=(const vec2d&v){x-=v.x; y-=v.y;return *this;}
  vec2d&operator*=(const real&f){x*=f;y*=f;return *this;}
  vec2d&operator/=(const real&f){x/=f;y/=f;return *this;}
public:
  vec2d Rot(const vec2d&OX)const{real M=OX.Mag();return vec2d(((x*+OX.x)+(y*OX.y))/M,((x*-OX.y)+(y*OX.x))/M);}
  vec2d UnRot(const vec2d&OX)const{real M=OX.Mag();if(M==0.0f){return vec2d(0,0);};return vec2d(((x*OX.x)+(y*-OX.y))/M,((x*OX.y)+(y*+OX.x))/M);}
  vec2d Ort()const{return vec2d(-y,x);}
  vec2d Norm()const{if((x==0)&&(y==0)){return vec2d(0,0);}return vec2d(x/this->Mag(),y/this->Mag());}
  vec2d SetMag(const real&val)const{return this->Norm().Mul(vec2d(val,val));}
  vec2d Mul(const vec2d&v)const{return vec2d(x*v.x,y*v.y);}
  vec2d Div(const vec2d&v)const{return vec2d(v.x!=0?x/v.x:x,v.y!=0?y/v.y:y);}
  real GetAng()const{return atan2(y,x);}
  real Mag()const{return sqrt(x*x+y*y);}
  real SqrMag()const{return x*x+y*y;}
public:
  real dist_to(const vec2d&p)const{return hypot(p.x-x,p.y-y);}
  real sqr_dist_to(const vec2d&p)const{return vec2d(p.x-x,p.y-y).SqrMag();}
  bool dist_to_point_less_that_r(const vec2d&p,real r)const{return vec2d(p.x-x,p.y-y).SqrMag()<r*r;}
public:
  static vec2d min(const vec2d&a,const vec2d&b){return vec2d(std::min(a.x,b.x),std::min(a.y,b.y));}
  static vec2d max(const vec2d&a,const vec2d&b){return vec2d(std::max(a.x,b.x),std::max(a.y,b.y));}
  static void comin(vec2d&a,const vec2d&b){a=min(a,b);}
  static void comax(vec2d&a,const vec2d&b){a=max(a,b);}
  static vec2d sign(const vec2d&p){return vec2d(Sign(p.x),Sign(p.y));}
public:
  inline static real dot(const vec2d&a,const vec2d&b){return a.x*b.x+a.y*b.y;}
  inline static real cross(const vec2d&a,const vec2d&b){return a.x*b.y-a.y*b.x;}
};
vec2d operator+(const vec2d&u,const vec2d&v){return vec2d(u.x+v.x,u.y+v.y);}
vec2d operator-(const vec2d&u,const vec2d&v){return vec2d(u.x-v.x,u.y-v.y);}
vec2d operator*(const vec2d&u,const real&v){return vec2d(u.x*v,u.y*v);}
vec2d operator*(const real&u,const vec2d&v){return vec2d(u*v.x,u*v.y);}
bool operator==(const vec2d&u,const vec2d&v){return (u.x==v.x)&&(u.y==v.y);}
bool operator!=(const vec2d&u,const vec2d&v){return !(u==v);}

inline vec2d Vec2dEx(const real&ang,const real&mag){return vec2d(cos(ang)*mag,sin(ang)*mag);}

template<class TYPE>
struct t_looped_buffer{
  vector<TYPE> frames;
  int n;
  int ptr;
public:
  t_looped_buffer(){n=8;ptr=0;}
  void add(const TYPE&value)
  {
    QapAssert(n>0);
    if(frames.size()!=n)frames.resize(n);
    ptr=ptr%n;
    frames[ptr]=value;
    ptr++;
    ptr=ptr%n;
  }
  void init(const TYPE&value){frames.resize(n,value);}
  TYPE&get_average(){
    TYPE sum;for(int i=0;i<frames.size();i++){sum+=frames[i];}
    return sum*(1.0/frames.size());
  }
};

using namespace model;
const Game*pgame=nullptr;
vec2d our_base_pos(000,4000);
vec2d real_our_base_pos(000,3600);
vec2d enemy_base_pos(-1,-1);
vec2d real_enemy_base_pos(-1,-1);
vec2d get_pos(const Unit&u){return vec2d(u.getX(),u.getY());}
real sqr(real x){return x*x;}

bool almost_equal(real a,real b,real eps=0.05){return abs(a-b)<eps;}

real get_selfdmgbon_mmmmm(const Wizard&ref){
  auto&arr=ref.skills;
  real k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_PASSIVE_1)k=1;
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_AURA_1)k=2;
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_PASSIVE_2)k=3;
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_AURA_2)k=4;
  }
  return k*pgame->magicalDamageBonusPerSkillLevel;
}

real get_selfdmgbon_staff(const Wizard&ref){
  auto&arr=ref.skills;
  real k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_STAFF_DAMAGE_BONUS_PASSIVE_1)k=1;
    if(ex==SKILL_STAFF_DAMAGE_BONUS_AURA_1)k=2;
    if(ex==SKILL_STAFF_DAMAGE_BONUS_PASSIVE_2)k=3;
    if(ex==SKILL_STAFF_DAMAGE_BONUS_AURA_2)k=4;
  }
  return k*pgame->staffDamageBonusPerSkillLevel;
}

real get_mmmmm_dmg(const Wizard&ref){
  return pgame->magicMissileDirectDamage+get_selfdmgbon_mmmmm(ref);
}

real get_staff_dmg(const Wizard&ref){
  return pgame->staffDamage+get_selfdmgbon_staff(ref);
}

static bool is_hastened(const Wizard&ref){
  auto&arr=ref.getStatuses();for(int i=0;i<arr.size();i++){auto&ex=arr[i];if(ex.getType()==STATUS_HASTENED)return true;}return false;
}
static const Status*get_hastened(const Wizard&ref){
  auto&arr=ref.getStatuses();for(int i=0;i<arr.size();i++){auto&ex=arr[i];if(ex.getType()==STATUS_HASTENED)return &ex;}return nullptr;
}
static real get_rotfactor(const Wizard&ref){return (is_hastened(ref)?1.0+pgame->getHastenedRotationBonusFactor():1.0);}

int get_passive_movbon_factor(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_MOVEMENT_BONUS_FACTOR_PASSIVE_1)k=1;
    if(ex==SKILL_MOVEMENT_BONUS_FACTOR_PASSIVE_2)k=2;
  }
  return k;
}

int get_aura_movbon_factor(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_MOVEMENT_BONUS_FACTOR_AURA_1)k=1;
    if(ex==SKILL_MOVEMENT_BONUS_FACTOR_AURA_2)k=2;
  }
  return k;
}

int get_passive_mdmgbon(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_PASSIVE_1)k=1;
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_PASSIVE_2)k=2;
  }
  return k;
}

int get_aura_mdmgbon(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_AURA_1)k=1;
    if(ex==SKILL_MAGICAL_DAMAGE_BONUS_AURA_2)k=2;
  }
  return k;
}

int get_passive_staffdmgbon(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_STAFF_DAMAGE_BONUS_PASSIVE_1)k=1;
    if(ex==SKILL_STAFF_DAMAGE_BONUS_PASSIVE_2)k=2;
  }
  return k;
}

int get_aura_staffdmgbon(const Wizard&ref){
  auto&arr=ref.skills;
  int k=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(ex==SKILL_STAFF_DAMAGE_BONUS_AURA_1)k=1;
    if(ex==SKILL_STAFF_DAMAGE_BONUS_AURA_2)k=2;
  }
  return k;
}

template<class TYPE>
int update_df(const vector<TYPE>&arr,vec2d&df,int&n,const Wizard&self)
{
  auto sp=get_pos(self);auto sr=self.getRadius();
  real gap=4*4+1;real hgap=gap/4;
  int tn=0;
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    if(self.getId()==ex.getId())continue;
    bool neutral=ex.getFaction()==FACTION_NEUTRAL;
    bool other=ex.getFaction()==FACTION_OTHER;
    bool enemy_active=ex.getLife()!=ex.getMaxLife();
    //if(neutral&&enemy_active)continue;
    //if(ex.getFaction()!=self.getFaction()&&!other)continue;
    if(other||(neutral&&!enemy_active))gap=hgap;
    auto ep=get_pos(ex);auto er=ex.getRadius();
    auto r=sr+er+gap;
    auto dist=ep.dist_to(sp);
    if(dist<r){
      //df=df+(sp-ep).SetMag(1.0-sqr((dist-sr-er)/gap));n++;
      df+=(sp-ep).Norm();n++;tn++;
    }
  }
  return tn;
}

real get_attsec(const Building&u){return Pi2;}
real get_attsec(const Wizard&ref){return pgame->getStaffSector();}
real get_attsec(const Minion&ref){return ref.getType()==MINION_ORC_WOODCUTTER?pgame->getOrcWoodcutterAttackSector():pgame->getFetishBlowdartAttackSector();}
real get_attrange(const Minion&ref){return ref.getType()==MINION_ORC_WOODCUTTER?pgame->getOrcWoodcutterAttackRange():pgame->getFetishBlowdartAttackRange();}
real get_attrange(const Wizard&ref){return ref.getCastRange();}
real get_attrange(const Building&ref){return ref.getAttackRange();}

struct t_tow{
  //int id;
  vec2d pos;
  int hp;
  real attrange;
  real r;
  real dmg;
  int cdt;
  int rcdt;
  Faction faction;
  BuildingType type;
  operator bool()const{return hp>0;}
};

static std::vector<t_tow> enemy_tows;

vec2d get_pos(const t_tow&u){return u.pos;}

real get_r(const CircularUnit&u){return u.getRadius();}
real get_r(const t_tow&u){return u.r;}

real get_ang(const CircularUnit&u){return u.getAngle();}
real get_ang(const t_tow&u){return 0;}

real get_attsec(const t_tow&u){return Pi2;}
real get_attrange(const t_tow&ref){return ref.attrange;}


int get_rcdt(const Wizard&e){return std::max(e.getRemainingCooldownTicksByAction()[ACTION_MAGIC_MISSILE],e.getRemainingActionCooldownTicks());}
template<class TYPE>int get_rcdt(const TYPE&e){return e.getRemainingActionCooldownTicks();}
int get_rcdt(const t_tow&e){return e.rcdt;}


struct t_shot_config{
  #define LIST(F)\
  F( -25,hp             ,100.0)\
  F(+100,attrange       ,500.0)\
  F( -10,rcdt           ,60.0)\
  F(+100,dmg            ,12.0)\
  F(  +1,dist           ,500.0)\
  F( -10,self_turn_ticks,30.0)\
  F(-1e3,self_rcdt      ,30.0)\
  F( +25,our_weapon_dmg ,12.0)\
  //      LIST
  #define F(koef,var,base)real var;
  LIST(F);
  #undef F
  t_shot_config(){
    #define F(koef,var,base)this->var=real(koef)/base;
    LIST(F);
    #undef F
  }
};

static const t_shot_config shot_conf;

int mmrad=0;
int mmdmg=0;

struct t_shot_state{
  int dist;
  int ang;
  real spd;
  t_shot_state(){dist=-1;ang=-1;spd=-1;}
  bool operator!=(const t_shot_state&ref)const{return dist!=ref.dist||ang!=ref.ang||spd!=ref.spd;}
};

struct t_shot{
  int wizid;
  vec2d ep;
  real er;
  int hp;
  real dmg;
  real dist;
  real self_turn_ticks;
  real attrange;
  int rcdt;
  bool ready;
  real profit;
  ActionType action;
  int self_rcdt;
  t_shot_state target_cast_state;
  real our_weapon_dmg;
  void update_profit(const vec2d&sp,real sr){
    auto&conf=shot_conf;
    #define F(var)var*conf.var
    profit=(
      F(hp)+F(attrange)+F(rcdt)+F(dmg)+F(dist)+F(self_turn_ticks)+F(self_rcdt)+F(our_weapon_dmg)
    );
    if(hp<=mmdmg*2)if(attrange>=499)profit+=F(attrange);
    auto base_dist=ep.dist_to(real_our_base_pos);
    auto danger_dist=attrange+pgame->factionBaseRadius+mmrad;
    if(base_dist<danger_dist){
      profit+=25.0*(danger_dist-base_dist)/danger_dist;
    }
    #undef F
  }
};

struct t_wizard_acc_stat{
  typedef t_shot_state t_state;
  struct t_rec{
    t_state state;
    int shots;
    int hits;
    t_rec(){shots=0;hits=0;}
    operator bool(){return shots<1||real(hits)/shots>0.45;}
    void add(bool hit){shots++;if(hit)hits++;}
  };
  int id;
  t_rec total;
  vector<t_rec> arr;
  void add_event(bool hit,t_state state){
    auto&rec=*dist2info(state);
    rec.add(hit);
    total.add(hit);
  }
  PRO_FUNCGEN_ADD_UNIQUE_OBJ_BY_FIELD_V2(t_rec,dist2info,arr,t_state,state);
};
vector<t_wizard_acc_stat> wizards_acc;
t_wizard_acc_stat final_wizacc;
PRO_FUNCGEN_ADD_UNIQUE_OBJ_BY_FIELD_V2(t_wizard_acc_stat,id2wizacc,wizards_acc,int,id);

struct t_magic_missle_target{
  int selfid;
  int wizid;
  t_shot_state target_cast_state;
  real beg_dist;
  real hp;
  real curhp;
  int tick;
  vec2d beg;
  vec2d end;
  void reset(){wizid=-1;hp=-1;tick=-1;curhp=-1;}
  t_magic_missle_target(){reset();}
};
vector<t_magic_missle_target> mm_targets;
PRO_FUNCGEN_ADD_UNIQUE_OBJ_BY_FIELD_V2(t_magic_missle_target,selfid2mmtarget,mm_targets,int,selfid);

struct t_lane{
  vector<t_tow*> arr;
  vec2d get_pos()const{
    for(int i=0;i<arr.size();i++)if(arr[i]->hp)return arr[i]->pos;
    return real_enemy_base_pos+(real_enemy_base_pos-real_our_base_pos).SetMag(pgame->factionBaseRadius*0.5);
  }
  bool unlocked()const{
    for(int i=0;i<arr.size();i++)if(arr[i]->hp)return false;
    return true;
  }
};

struct t_main_tower_info{
  t_lane top;
  t_lane mid;
  t_lane low;
  const t_lane&operator[](size_t id)const{return (&top)[id%3];}
  t_lane&operator[](size_t id){return (&top)[id%3];}
  bool unlocked()const{
    auto&arr=*this;
    for(int i=0;i<3;i++)if(arr[i].unlocked())return true;
    return false;
  }
};

t_main_tower_info enemy_main_tower;

struct t_unit{
  int id;
  vec2d pos;
  real ang;
  bool neutral;
  bool agro;
  t_looped_buffer<vec2d> loop_pos;
  t_looped_buffer<real> loop_ang;
  void load(const LivingUnit&ex){
    id=ex.getId();
    pos=get_pos(ex);
    ang=get_ang(ex);
    neutral=ex.getFaction()==FACTION_NEUTRAL;
    agro=false;
    if(loop_pos.frames.empty())loop_pos.init(pos);
    loop_pos.add(pos);
    if(loop_ang.frames.empty())loop_ang.init(ang);
    loop_ang.add(ang);
  }
  template<class TYPE>
  void update(const TYPE&ex){
    if(!neutral){load(ex);return;}
    if(get_pos(ex).dist_to(pos)>0.1)agro=true;
    if(abs(get_ang(ex)-ang)>0.1)agro=true;
    if(get_rcdt(ex))agro=true;
    if(ex.getLife()!=ex.getMaxLife())agro=true;
  }
};

vector<t_unit> units;
PRO_FUNCGEN_GETP_BY_FIELD(t_unit,id2unit,units,int,id);

template<class TYPE>
void load_units(const vector<TYPE>&arr){
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    auto*p=id2unit(ex.getId());
    if(!p){p=&qap_add_back(units);p->load(ex);continue;}
    p->update(ex);
  }
}

struct t_tree{
  int tick;
  vec2d pos;
  real r;
  int hp;
  t_tree(){tick=-1;hp=-1;r=0;}
  void load(const Tree&ex,int t){
    tick=t;
    pos=get_pos(ex);
    r=ex.getRadius();
    hp=ex.getLife();
  }
};

vector<t_tree> id2tree;
vector<int> trees;

void update_forest(const vector<Tree>&arr,int tick){
  for(int i=0;i<arr.size();i++){
    auto&ex=arr[i];
    auto id=ex.getId();
    if(id>=id2tree.size())id2tree.resize(id+1);
    id2tree[id].load(ex,tick);
  }
}

bool is_passive_and_neutral(const t_tow&ex){return false;}
bool is_passive_and_neutral(const Building&ex){return false;}
bool is_passive_and_neutral(const Wizard&ex){return false;}
bool is_passive_and_neutral(const Minion&ex){
  auto*p=id2unit(ex.getId());
  QapAssert(p);
  return p->neutral&&!p->agro;
}

int g_low_hp_ewiz_id=-1;

struct MeWorld:public World
{
  real get_movfactor(const Wizard&ref)const{
    return (is_hastened(ref)?1.0+pgame->hastenedMovementBonusFactor:1.0)+get_selfmovbon(ref);
  }
  real get_movfactor_with_timelimit(const Wizard&ref,int TL=16)const{
    if(auto*p=get_hastened(ref))if(p->getRemainingDurationTicks()<TL)return 1+get_selfmovbon(ref);return get_movfactor(ref);
  }
  vec2d movedir2input(const Game&game,const Wizard&self,const vec2d&dir)const{
    auto rf=get_rotfactor(self);auto mf=get_movfactor(self);
    auto sk=game.getWizardStrafeSpeed();
    auto fk=game.getWizardForwardSpeed();
    auto bk=game.getWizardBackwardSpeed();
    QapAssert(almost_equal(sk,bk,1e-4));
    auto m=vec2d(fk,sk);
    auto out=dir.x<=0?dir.SetMag(sk):dir.Div(m).Norm().Mul(m)*mf;
    return out;
  }

  void set_move(const Game&game,const Wizard&self,Move&move,const vec2d&dir)const{
    auto out=movedir2input(game,self,dir);
    move.setStrafeSpeed(out.y);
    move.setSpeed(out.x);
  }
  real get_selfmovbon(const Wizard&ref)const{
    real k=get_passive_movbon_factor(ref)+get_aura_movbon_factor_in_point(get_pos(ref),ref.faction);
    return k*pgame->movementBonusFactorPerSkillLevel;
  }
  int get_aura_movbon_factor_in_point(const vec2d&p,const Faction&faction)const{
    auto&arr=wizards;int k=0;
    QAP_FOREACH(arr,if(ex.faction==faction)if(get_pos(ex).dist_to_point_less_that_r(p,pgame->auraSkillRange))k=std::max(k,get_aura_movbon_factor(ex)););
    return k;
  }
  real get_selfmdmgbon(const Wizard&ref)const{
    real k=get_passive_mdmgbon(ref)+get_aura_mdmgbon_in_point(get_pos(ref),ref.faction);
    return k*pgame->magicalDamageBonusPerSkillLevel;
  }
  int get_aura_mdmgbon_in_point(const vec2d&p,const Faction&faction)const{
    auto&arr=wizards;int k=0;
    QAP_FOREACH(arr,if(ex.faction==faction)if(get_pos(ex).dist_to_point_less_that_r(p,pgame->auraSkillRange))k=std::max(k,get_aura_mdmgbon(ex)););
    return k;
  }
  real get_selfstaffdmgbon(const Wizard&ref)const{
    real k=get_passive_staffdmgbon(ref)+get_aura_staffdmgbon_in_point(get_pos(ref),ref.faction);
    return k*pgame->staffDamageBonusPerSkillLevel;
  }
  int get_aura_staffdmgbon_in_point(const vec2d&p,const Faction&faction)const{
    auto&arr=wizards;int k=0;
    QAP_FOREACH(arr,if(ex.faction==faction)if(get_pos(ex).dist_to_point_less_that_r(p,pgame->auraSkillRange))k=std::max(k,get_aura_staffdmgbon(ex)););
    return k;
  }
  template<class TYPE>
  bool is_visible_ex(const vec2d&p,const vector<TYPE>&arr,const Faction&frac){
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      if(ex.getFaction()!=frac)continue;
      bool ok=get_pos(ex).dist_to_point_less_that_r(p,ex.getVisionRange());
      if(ok)return true;
    }
    return false;
  }
  bool is_visible(const vec2d&p,const Wizard&self){
    auto our_frac=self.getFaction();
    if(is_visible_ex(p,getMinions(),our_frac))return true;
    if(is_visible_ex(p,getWizards(),our_frac))return true;
    if(is_visible_ex(p,getBuildings(),our_frac))return true;
    return false;
  }
  const Building*get_tow_at_pos(const vec2d&pos){
    auto&arr=getBuildings();
    for(int i=0;i<arr.size();i++){auto&ex=arr[i];if(get_pos(ex).dist_to(pos)<1)return &ex;};
    return nullptr;
  }
  t_tow&get_etow_at_pos(const vec2d&pos){
    auto&arr=enemy_tows;
    for(int i=0;i<arr.size();i++){auto&ex=arr[i];if(ex.pos.dist_to(pos)<1)return ex;};
    return *(t_tow*)nullptr;
  }
  void update(t_tow&tow,const Wizard&self){
    if(!tow.hp)return;
    if(!is_visible(tow.pos,self))return;
    auto*p=get_tow_at_pos(tow.pos);
    if(p)tow.pos=get_pos(*p);
    tow.hp=p?p->getLife():0;
    tow.rcdt=p?p->getRemainingActionCooldownTicks():0;
  }
  // for wizrd std::max(e.getRemainingCooldownTicksByAction()[ACTION_MAGIC_MISSILE],e.getRemainingActionCooldownTicks())
  template<class TYPE>int get_maxcdt(const TYPE&e){return e.getCooldownTicks();}
  int get_maxcdt(const Wizard&e){return pgame->getMagicMissileCooldownTicks();}
  int get_maxcdt(const t_tow&e){return e.cdt;}

  // without other enviroment objects. just for r1.
  struct t_input{
    vec2d dpos;
    real dang;
  };
  
  struct t_wiz{
    vec2d pos;
    real hp;
    real ang;
    real angspd;
    real attsec;
    real attrange;
    real bulletspd;
    real rotf;
    real movf;
    real fspd;
    real sspd;
    real bspd;
    int mm_rcdt;
    int sf_rcdt;
    void load(const MeWorld&world,const Wizard&ref){
      pos=get_pos(ref);
      hp=get_hp(ref);
      ang=get_ang(ref);
      angspd=get_angspd(ref);
      attsec=get_attsec(ref);
      attrange=get_attrange(ref);
      bulletspd=get_maxbulletspd(ref);
      rotf=get_rotfactor(ref);
      movf=world.get_movfactor(ref);
      sspd=pgame->getWizardStrafeSpeed();
      fspd=pgame->getWizardForwardSpeed();
      bspd=pgame->getWizardBackwardSpeed();
      auto min_rcdt=ref.getRemainingActionCooldownTicks();
      mm_rcdt=std::max(min_rcdt,ref.getRemainingCooldownTicksByAction()[ACTION_MAGIC_MISSILE]);
      sf_rcdt=std::max(min_rcdt,ref.getRemainingCooldownTicksByAction()[ACTION_STAFF]);
    }
    vec2d clamp_movespeedinput(real speed,real strafe){
      return vec2d(Clamp(speed,fspd*movf,bspd*movf),Clamp(strafe,-sspd*movf,+sspd*movf));
    }
    vec2d movedir2input(const vec2d&dir){
      QapAssert(almost_equal(sspd,bspd,1e-4));
      auto m=vec2d(fspd,bspd);
      auto out=dir.x<=0?dir.SetMag(sspd):dir.Div(m).Norm().Mul(m)*movf;
      return out;
    }
    void sim_step(const t_input&ref){
      auto dpos=clamp_movespeedinput(ref.dpos.x,ref.dpos.y).UnRot(Vec2dEx(ang,1));
      pos+=dpos;
      ang+=Clamp(ref.dang,-angspd*rotf,+angspd*rotf);
      mm_rcdt=std::max(0,mm_rcdt-1);
      sf_rcdt=std::max(0,sf_rcdt-1);
    }
    t_input get_input_to_dir(vec2d dir){
      auto movdir=dir.Rot(Vec2dEx(ang,1));
      t_input inp;
      inp.dang=movdir.GetAng();
      inp.dpos=movedir2input(movdir);
      return inp;
    }
  };

  int cur_entrypoint()
  {
    return 0;
  }

  real get_fly_ticks_v2(vec2d pos,const vec2d&v,int wizr,const vector<t_wiz>&sarr,int offset,real ecr)
  {
    int n=2;real inv_n=1.0/n;auto sv=v*inv_n;auto beg_pos=pos;int subiter=0;int maxsubiter=ecr*n/v.Mag();
    for(int iter=0;;iter++)
    {
      auto&wiz=sarr[offset+iter];
      for(int i=0;i<n;i++){
        if(pos.dist_to_point_less_that_r(wiz.pos,mmrad*2+wizr))return subiter*inv_n;
        if(subiter>=maxsubiter)return -subiter*inv_n;
        pos+=sv;
        subiter++;
      }
    }
    return -0.1234567;
  }

  bool sim_based_go_back(const Wizard&self,const Wizard&enemy,const vec2d&dir)
  {
    vector<t_wiz> sarr;
    t_wiz s;s.load(*this,self);
    t_wiz e;e.load(*this,enemy);
    if(!s.pos.dist_to_point_less_that_r(e.pos,self.getVisionRange()*1.25))return false;
    int limit=30+60+12*2;
    for(int t=0;t<limit+16;t++)
    {
      auto sinp=s.get_input_to_dir(t?-dir:+dir);
      sarr.push_back(s);
      s.sim_step(sinp);
    }
    auto ecr=enemy.getCastRange();auto hss=pgame->getStaffSector()*0.5;auto wizr=self.getRadius();
    for(int t=0;t<limit;t++)
    {
      auto einp=e.get_input_to_dir(sarr[t].pos-e.pos);
      //auto sinp=s.get_input_to_dir(t?-dir:dir);
      if(!e.mm_rcdt)
      {
        auto ang=fabs((s.pos-e.pos).Rot(Vec2dEx(e.ang,1)).GetAng());
        if(ang<hss)
        {
          int mid_rays=64;
          for(int i=0;i<=mid_rays+1;i++)
          {
            real k=i*hss*2/(mid_rays+1);
            vec2d bullet_v=Vec2dEx(e.ang-hss+k,e.bulletspd);
            //auto ft=get_fly_ticks(e.pos,bullet_v,s,wizr,-dir,ecr);
            auto ft=get_fly_ticks_v2(e.pos,bullet_v,wizr,sarr,t,ecr);
            bool hit=ft>=0;
            if(!hit)
            {
              int gg=1;
              continue;
            }
            int gg=1;
            return true;
          }

          //auto bullet_fly_ticks=real_to_int_up(dist/get_maxbulletspd(self));
          //if(e.pos.dist_to(s.pos)<ecr+wizr+mmrad)
        }
        int gg=1;
      }
      e.sim_step(einp);
      //s.sim_step(sinp);
    }
    return false;
  }

  struct t_go_back_result{
    bool go_back;
    bool go_fast;
    bool go_panic;
    void add(const t_go_back_result&ref){
      go_back=go_back||ref.go_back;
      go_fast=go_fast||ref.go_fast;
      go_panic=go_panic||ref.go_panic;
    }
  };

  t_go_back_result need_go_back(const Wizard&self,real shp,real smf,const vec2d&sp,real sr,const vec2d&dir,const Wizard&e)
  {
    t_go_back_result out={false,false,false};
    if(e.getId()==g_low_hp_ewiz_id&&get_hp(e)<shp-mmdmg*3){
      return out;
    }
    if(shp>=self.maxLife*0.5)return need_go_back<Wizard>(self,shp,smf,sp,sr,dir,e);
    out.go_back=sim_based_go_back(self,e,dir);
    if(out.go_back){
      int gg=1;
    }
    out.go_fast=out.go_back;
    auto ehp=get_hp(e);
    if(out.go_back)if(shp-mmdmg*2>=ehp){
      out.go_fast=false;
    }
    return out;
  }
  struct t_wizwall{
    vec2d center;
    int n;
    int hp;
    int tn;
    int thp;
    real get_avr_thp(){return !tn?0:real(thp)/tn;}
  };
  bool inside_wizwall(const Wizard&self,t_wizwall&wall){
    return wall.center.dist_to_point_less_that_r(get_pos(self),pgame->wizardCastRange);
  }
  t_wizwall get_wizwall(const Unit&ref){QapAssert(false);t_wizwall tmp={get_pos(ref)};return tmp;}
  t_wizwall get_wizwall(const t_tow&ref){QapAssert(false);t_wizwall tmp={get_pos(ref)};return tmp;}
  template<class TYPE>
  t_go_back_result need_go_back(const Wizard&self,real shp,real smf,const vec2d&sp,real sr,const vec2d&dir,const TYPE&e){
    bool go_back=false;bool go_fast=false;bool go_panic=false;
    real wiz_buff=3.1;
    auto final_mode=pgame->rawMessagesEnabled;
    const real self_bspd=pgame->getWizardBackwardSpeed()*smf;
    const real self_fspd=pgame->getWizardForwardSpeed()*smf;
    const real bot_spd=3;
    auto bulletrad=get_bulletrad(e);
    auto ehp=get_hp(e);
    auto ep=get_pos(e);
    auto ang=get_ang(e);
    auto angspd=get_angspd(e);
    auto attsec=get_attsec(e);
    auto bulletspd=get_maxbulletspd(e);
    auto maxspd=get_maxspd(e);
    auto is_ewiz=maxspd>bot_spd;
    if(is_ewiz&&final_mode)
    {
      if(shp>ehp||(shp==self.maxLife&&shp==ehp))if(shp>64)wiz_buff=-25;
      auto wall=get_wizwall(self);
      auto ewall=get_wizwall(e);
      if(shp>24)if(wall.n>=2||(wall.tn>ewall.tn&&wall.thp>=ewall.thp+64))if(wall.get_avr_thp()>ewall.get_avr_thp()+24)wiz_buff=-64;
    }
    /*
    if(!almost_equal(self_bspd,maxspd)&&self_bspd<maxspd){
      go_panic=!almost_equal(self_fspd,maxspd)&&self_fspd<maxspd;
      if(go_panic)if(sp.dist_to(ep)>get_attrange(e)+sr*8+bulletrad)go_panic=false;
      if(almost_equal(self_fspd,maxspd)||go_panic){
        //+6.1940176041876 in 30 frames; from bspd to fspd
        wiz_buff+=+6.1940176041876+self_fspd;
        go_fast=true;
      }
    }
    */
    if(go_panic)wiz_buff*=2;
    auto spd=get_spd(e);
    int dodge_ticks=std::max(0,real_to_int_up((sp.dist_to(ep)-sr-bulletrad)/real(bulletspd))-1);
    auto turn_ticks=get_min_turn_ticks(sp,ep,ang,attsec,angspd);
    auto safe_ticks=std::max(0,std::max(turn_ticks,get_rcdt(e)));
    auto safe_dist=safe_ticks*std::max(0.0,self_bspd-maxspd);
    bool look_like_tower=almost_equal(spd.SqrMag(),0)&&almost_equal(3,maxspd)&&bulletrad>0;
    if(look_like_tower){
      safe_dist=safe_ticks*self_bspd;//wiz_buff=0;
    }
    //bool is_fetish=almost_equal(spd.SqrMag(),0)&&almost_equal(self_spd,maxspd)&&bulletrad>0;
    //bool is_orcwod=almost_equal(spd.SqrMag(),0)&&almost_equal(self_spd,maxspd)&&!bulletrad;
    //if(is_fetish)safe_dist=safe_ticks*self_spd;
    //if(is_orcwod)safe_dist=safe_ticks*self_spd;
    //if(almost_equal(self_spd,maxspd)&&!bulletrad)safe_ticks=0;
    //bool turn_ticks_based_answer=;
    //bool cdt_based_answer=(sp-dir.SetMag(get_rcdt(e)*2.9)).dist_to(ep)<=get_attrange(e)+sr+4.1;
    go_back=(sp-dir.SetMag(self_bspd*dodge_ticks+safe_dist)).dist_to(ep)<=get_attrange(e)+sr+bulletrad+wiz_buff;
    /*
    if(is_ewiz)if(go_panic)if(shp+mmdmg*3>=ehp){go_panic=false;go_back=false;}
    if(is_ewiz)if(go_panic)if(shp/ehp>3){go_panic=false;go_back=false;}
    */
    t_go_back_result out={go_back,go_back?go_fast:false,go_panic};
    return out;
  }
  bool is_vulnerable(const CircularUnit&u){return true;}
  bool is_vulnerable(const t_tow&u){
    if(u.hp<=0)return false;
    //auto&tow=get_etow_at_pos(get_pos(u));
    for(int i=0;i<3;i++){
      auto&ex=enemy_main_tower[i];
      if(ex.arr[1]==&u)return ex.arr[0]->hp<=0;
    }
    return u.type==BUILDING_FACTION_BASE?enemy_main_tower.unlocked():true;
  }
  
  bool is_ebase(const CircularUnit&u){return false;}
  bool is_ebase(const t_tow&u){return u.type==BUILDING_FACTION_BASE;}
  static int get_hp(const LivingUnit&u){return u.getLife();}
  static int get_hp(const t_tow&u){return u.hp;}
  static real get_angspd(const t_tow&u){return Pi2;}
  static real get_angspd(const Building&u){return Pi2;}
  static real get_angspd(const Minion&ref){return pgame->getMinionMaxTurnAngle();}
  static real get_angspd(const Wizard&ref){return get_rotfactor(ref)*pgame->getWizardMaxTurnAngle();}
  static real get_maxbulletspd(const Wizard&ref){return pgame->getMagicMissileSpeed();}
  static real get_maxbulletspd(const t_tow&ref){return 4000;}
  static real get_maxbulletspd(const Building&ref){return 4000;}
  static real get_maxbulletspd(const Minion&ref){return ref.getType()==MINION_ORC_WOODCUTTER?4000:pgame->getDartSpeed();}
  real get_maxspd(const Wizard&ref){return get_movfactor(ref)*pgame->getWizardForwardSpeed();}
  static real get_maxspd(const t_tow&ref){return 0;}
  static real get_maxspd(const Building&ref){return 0;}
  static real get_maxspd(const Minion&ref){return pgame->getMinionSpeed();}
  static bool has_staff(const Wizard&){return true;}
  static bool has_mm(const Wizard&){return true;}
  static bool has_fireball(const Wizard&ref){return qap_includes(ref.skills,SKILL_FIREBALL);}
  static bool has_frostbolt(const Wizard&ref){return qap_includes(ref.skills,SKILL_FROST_BOLT);}
  enum t_weapon_type{ew_dart,ew_mm,ew_fi,ew_fr,ew_st};
  struct t_weapon_info{
    real r;
    real spd;
    real dmg;
    real mindmg;
    int rcdt;
    int mcost;
    //t_weapon_type type;
  };
  static real get_mana_regspd(const Wizard&ref){
    return pgame->wizardBaseManaRegeneration+pgame->wizardManaRegenerationGrowthPerLevel*ref.level;;
  }
  static int mp_based_rcdt(const Wizard&ref,int mpcost){
    auto mrspd=get_mana_regspd(ref);
    auto mrcdt=real_to_int_up(std::max(0.0,(mpcost-ref.mana)/mrspd));
    return mrcdt;
  }
  vector<t_weapon_info> get_weapons(const Wizard&ref){
    auto self_rcdt_act=ref.getRemainingActionCooldownTicks();
    vector<t_weapon_info> out;
    if(has_staff(ref))
    {
      auto self_rcdt_staff=std::max(self_rcdt_act,ref.getRemainingCooldownTicksByAction()[ACTION_STAFF]);
      auto&b=qap_add_back(out);
      b.mcost=0;
      b.r=0;
      b.spd=4000;
      b.dmg=pgame->staffDamage+get_selfstaffdmgbon(ref);
      auto mrcdt=mp_based_rcdt(ref,b.mcost);
      b.rcdt=std::max(self_rcdt_act,std::max(mrcdt,self_rcdt_staff));
    }
    if(has_mm(ref))
    {
      auto self_rcdt_mm=std::max(self_rcdt_act,ref.getRemainingCooldownTicksByAction()[ACTION_MAGIC_MISSILE]);
      auto&b=qap_add_back(out);
      b.mcost=pgame->magicMissileManacost;
      b.r=pgame->magicMissileRadius;
      b.spd=pgame->magicMissileSpeed;
      b.dmg=pgame->magicMissileDirectDamage+get_selfmdmgbon(ref);
      auto mrcdt=mp_based_rcdt(ref,b.mcost);
      b.rcdt=std::max(self_rcdt_act,std::max(mrcdt,self_rcdt_mm));
    }
    if(has_fireball(ref))
    {
      auto self_rcdt_fi=std::max(self_rcdt_act,ref.getRemainingCooldownTicksByAction()[ACTION_FIREBALL]);
      auto&b=qap_add_back(out);
      b.mcost=pgame->fireballManacost;
      b.r=pgame->fireballRadius;
      b.spd=pgame->fireballSpeed;
      b.dmg=pgame->fireballExplosionMaxDamage;
      auto mrcdt=mp_based_rcdt(ref,b.mcost);
      b.rcdt=std::max(self_rcdt_act,std::max(mrcdt,self_rcdt_fi));
    }
    if(has_frostbolt(ref))
    {
      auto self_rcdt_fr=std::max(self_rcdt_act,ref.getRemainingCooldownTicksByAction()[ACTION_FROST_BOLT]);
      auto&b=qap_add_back(out);
      b.mcost=pgame->frostBoltManacost;
      b.r=pgame->frostBoltRadius;
      b.spd=pgame->frostBoltSpeed;
      b.dmg=pgame->frostBoltDirectDamage;
      auto mrcdt=mp_based_rcdt(ref,b.mcost);
      b.rcdt=std::max(self_rcdt_act,std::max(mrcdt,self_rcdt_fr));
    }
    return out;
  }
  static real get_bulletrad(const Wizard&ref){
    if(has_frostbolt(ref)){
      pgame->frostBoltRadius;
    }
    return mmrad;
  }
  static real get_bulletrad(const t_tow&ref){return 0;}
  static real get_bulletrad(const Building&ref){return 0;}
  static real get_bulletrad(const Minion&ref){return ref.getType()==MINION_ORC_WOODCUTTER?0:pgame->getDartRadius();}
  template<class TYPE>static int get_dmg(const TYPE&u){return u.getDamage();}
  static int get_dmg(const Wizard&u){return pgame->getMagicMissileDirectDamage();}
  static int get_dmg(const t_tow&u){return u.dmg;}
  //static int get_id(const Unit&u){return u.getId();}
  //static int get_id(const t_tow&u){return -1;}
  static int get_wizid(const Wizard&u){return u.getId();}
  static int get_wizid(const Unit&u){return -1;}
  static int get_wizid(const t_tow&u){return -1;}
  static vec2d get_spd(const t_tow&ref){return vec2d(0,0);}
  static vec2d get_spd(const CircularUnit&ref){return vec2d(ref.getSpeedX(),ref.getSpeedY());}
  static int real_to_int_up(real n){return real(int(n))==n?n:int(n)+1;}
  int get_min_turn_ticks(vec2d target,vec2d pos,real ang,real attsec,real angspd){
    auto n=std::max(0.0,abs((target-pos).Rot(Vec2dEx(ang,1)).GetAng())-attsec*0.5)/angspd;
    return real_to_int_up(n);// TODO: how about move&turn?
  }
  template<class TYPE>int get_rcdt_minus_fly_ticks(const TYPE&ex,int fly_tick){auto a=get_rcdt(ex);auto b=get_maxcdt(ex);return (b*1024+a-fly_tick)%b;}
  int wizang2wizangid(real ang){return int(abs(ang)*5.0/Pi);}
  t_shot_state wizid2personal_cast_range(vec2d to_ewiz,int wizid,real maxvalue,real cr)
  {
    t_shot_state def;def.dist=maxvalue;def.ang=0;def.spd=0;
    auto final_mode=pgame->rawMessagesEnabled;
    if(wizid<0)return def;
    auto*pwiz=id2wiz(wizid);
    QapAssert(pwiz);if(!pwiz)return def;
    auto&wiz=*pwiz;
    t_wizard_acc_stat::t_state state;
    state.ang=wizang2wizangid(Vec2dEx(wiz.angle,1).Rot(-to_ewiz).GetAng());
    state.spd=get_maxspd(wiz);
    state.dist=maxvalue;
    auto*p=final_mode?&final_wizacc:id2wizacc(wizid);
    auto dist2range=[&state,&p](real dist)->t_wizard_acc_stat::t_rec&{state.dist=dist;return *p->dist2info(state);};
    {
      auto&maxrange=dist2range(maxvalue);
      if(maxrange)return maxrange.state;
    }
    auto movf=get_movfactor(wiz);
    static const real bspd=pgame->getWizardBackwardSpeed();
    static const real fspd=pgame->getWizardForwardSpeed();
    static const real r=wiz.radius;
    static const real mmspd=pgame->getMagicMissileSpeed();
    {
      auto midvalue=maxvalue-((cr*bspd*movf/mmspd)-mmrad);
      auto&midrange=dist2range(midvalue);
      if(midrange)return midrange.state;
    }
    {
      auto lowvalue=maxvalue-(cr*fspd*movf/mmspd)-mmrad;
      auto&info=dist2range(lowvalue);
      if(info||!final_mode)return info.state;
    }
    for(int i=1;i<16;i++)
    {
      auto v=maxvalue-(cr*fspd*movf/mmspd)-mmrad-r*0.5*i;
      auto&info=dist2range(v);
      if(info)return info.state;
    }
    return def;
  }
  template<class TYPE>
  t_go_back_result update_enemy_arr(vector<t_shot>&out,const vector<TYPE>&arr,const Wizard&self,const Game&game,Move&move,const vec2d&ox)
  {
    auto mp_based_mm_rcdt=pgame->magicMissileManacost/get_mana_regspd(self);
    auto mmdmg=get_mmmmm_dmg(self);
    auto sfdmg=get_staff_dmg(self);
    real ex_attrange_gap=0;
    if(self.getLife()<mmdmg*2.1){ex_attrange_gap=self.getRadius()*4;}
    if(self.getLife()<mmdmg*3.1){ex_attrange_gap=self.getRadius()*2;}
    t_go_back_result out_bfp={false,false,false};
    auto sp=get_pos(self);auto sr=self.getRadius();auto sp_ox=sp.Rot(ox);auto sx_attrange=self.getCastRange();auto shp=get_hp(self);
    auto smf=get_movfactor_with_timelimit(self);
    auto sx_ang=get_ang(self);auto sx_angspd=get_angspd(self);auto sx_attsec=get_attsec(self);
    auto self_rcdt_act=self.getRemainingActionCooldownTicks();
    auto self_rcdt_mmmmm=std::max(self_rcdt_act,self.getRemainingCooldownTicksByAction()[ACTION_MAGIC_MISSILE]);
    auto self_rcdt_staff=std::max(self_rcdt_act,self.getRemainingCooldownTicksByAction()[ACTION_STAFF]);
    auto self_rcdt_frost=std::max(self_rcdt_act,self.getRemainingCooldownTicksByAction()[ACTION_FROST_BOLT]);
    auto self_rcdt_fire=std::max(self_rcdt_act,self.getRemainingCooldownTicksByAction()[ACTION_FIREBALL]);
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      if(is_passive_and_neutral(ex))continue;
      if(ex.faction==self.faction)continue;
      auto ep=get_pos(ex);auto er=get_r(ex);auto ep_ox=ep.Rot(ox);
      auto dist=ep.dist_to(sp);
      auto ex_attrange=std::max(sx_attrange,get_attrange(ex))+ex_attrange_gap;
      auto bullet_fly_ticks=real_to_int_up(dist/get_maxbulletspd(self));
      auto personal_cast_range=wizid2personal_cast_range(ep-sp,get_wizid(ex),self.getCastRange()+er+mmrad-0.2,sx_attrange);
      if(is_vulnerable(ex))
      {
        if(dist<personal_cast_range.dist)if(has_frostbolt(self))
        {
          self_rcdt_frost=std::max(mp_based_rcdt(self,pgame->frostBoltManacost),self_rcdt_frost);
          auto bullet_fly_ticks=real_to_int_up(dist/pgame->frostBoltSpeed);
          if(self_rcdt_frost<mp_based_mm_rcdt)
          {
            auto&shot=qap_add_back(out);
            shot.wizid=get_wizid(ex);
            shot.ep=get_pos(ex);
            shot.ep=ep;
            shot.er=er;
            shot.rcdt=get_rcdt_minus_fly_ticks(ex,bullet_fly_ticks);
            shot.hp=get_hp(ex);
            shot.dmg=get_dmg(ex);
            shot.dist=dist;
            shot.attrange=get_attrange(ex);
            double angle=self.getAngleTo(ep.x,ep.y);
            shot.self_turn_ticks=std::max(0,get_min_turn_ticks(ep,sp,sx_ang,sx_attsec,sx_angspd)-self_rcdt_frost);
            shot.ready=abs(angle)<game.getStaffSector()/2.0;
            shot.action=ACTION_FROST_BOLT;
            shot.self_rcdt=self_rcdt_frost;
            shot.target_cast_state=personal_cast_range;
            shot.our_weapon_dmg=pgame->frostBoltDirectDamage;
          }
        }
        if(dist<personal_cast_range.dist)if(has_fireball(self))
        {
          self_rcdt_fire=std::max(mp_based_rcdt(self,pgame->fireballManacost),self_rcdt_fire);
          auto bullet_fly_ticks=real_to_int_up(dist/pgame->fireballSpeed);
          if(self_rcdt_fire<mp_based_mm_rcdt)
          {
            auto&shot=qap_add_back(out);
            shot.wizid=get_wizid(ex);
            shot.ep=get_pos(ex);
            shot.ep=ep;
            shot.er=er;
            shot.rcdt=get_rcdt_minus_fly_ticks(ex,bullet_fly_ticks);
            shot.hp=get_hp(ex);
            shot.dmg=get_dmg(ex);
            shot.dist=dist;
            shot.attrange=get_attrange(ex);
            double angle=self.getAngleTo(ep.x,ep.y);
            shot.self_turn_ticks=std::max(0,get_min_turn_ticks(ep,sp,sx_ang,sx_attsec,sx_angspd)-self_rcdt_fire);
            shot.ready=abs(angle)<game.getStaffSector()/2.0;
            shot.action=ACTION_FIREBALL;
            shot.self_rcdt=self_rcdt_fire;
            shot.target_cast_state=personal_cast_range;
            shot.our_weapon_dmg=pgame->fireballExplosionMaxDamage;
          }
        }
        if(dist<personal_cast_range.dist)
        {
          auto&shot=qap_add_back(out);
          shot.wizid=get_wizid(ex);
          shot.ep=get_pos(ex);
          shot.ep=ep;
          shot.er=er;
          shot.rcdt=get_rcdt_minus_fly_ticks(ex,bullet_fly_ticks);
          shot.hp=get_hp(ex);
          shot.dmg=get_dmg(ex);
          shot.dist=dist;
          shot.attrange=get_attrange(ex);
          double angle=self.getAngleTo(ep.x,ep.y);
          shot.self_turn_ticks=std::max(0,get_min_turn_ticks(ep,sp,sx_ang,sx_attsec,sx_angspd)-self_rcdt_mmmmm);
          shot.ready=abs(angle)<game.getStaffSector()/2.0;
          shot.action=ACTION_MAGIC_MISSILE;
          shot.self_rcdt=self_rcdt_mmmmm;
          shot.target_cast_state=personal_cast_range;
          shot.our_weapon_dmg=mmdmg;
        }
        if(dist<game.getStaffRange()+er-0.2)
        {
          auto&shot=qap_add_back(out);
          shot.wizid=get_wizid(ex);
          shot.ep=get_pos(ex);
          shot.ep=ep;
          shot.er=er;
          shot.rcdt=get_rcdt_minus_fly_ticks(ex,0);
          shot.hp=get_hp(ex);
          shot.dmg=get_dmg(ex);
          shot.dist=dist;
          shot.attrange=get_attrange(ex);
          double angle=self.getAngleTo(ep.x,ep.y);
          shot.self_turn_ticks=std::max(0,get_min_turn_ticks(ep,sp,sx_ang,sx_attsec,sx_angspd)-self_rcdt_staff);
          shot.ready=abs(angle)<game.getStaffSector()/2.0;
          shot.action=ACTION_STAFF;
          shot.self_rcdt=self_rcdt_staff;
          shot.target_cast_state=personal_cast_range;
          shot.our_weapon_dmg=sfdmg;
        }
      }
      auto bfp=need_go_back(self,shp,smf,sp,sr,ox,ex);
      auto final_mode=game.rawMessagesEnabled;
      if(!final_mode||(final_mode&&!is_ebase(ex)))out_bfp.add(bfp);
      bool need_def_our_base=false;
      //if(final_mode&&(self.id-1)%5>2)need_def_our_base=true;
      if(ep_ox.x<=sp_ox.x&&abs((ep_ox-sp_ox).y)<ex_attrange&&(need_def_our_base||abs((ep_ox-sp_ox).x)<ex_attrange))out_bfp.go_back=true;
    }
    return out_bfp;
  }
  void do_shot(t_shot&shot,const Wizard&self,const Game&game,Move&move,const vec2d&ox)
  {
    auto final_mode=game.rawMessagesEnabled;
    auto&mm_target=*selfid2mmtarget(self.id);
    //auto mmrad=game.getMagicMissileRadius();
    auto sp=get_pos(self);//auto sr=self.getRadius();auto sp_ox=sp.Rot(ox);auto sx_attrange=self.getCastRange();
    auto ep=shot.ep;auto er=shot.er;auto ep_ox=ep.Rot(ox);
    auto dist=ep.dist_to(sp);
      double angle=self.getAngleTo(ep.x,ep.y);
    move.setTurn(angle);
    if(!shot.ready)return;
    move.setAction(shot.action);
    move.setCastAngle(angle);
    move.setMinCastDistance(shot.action==ACTION_STAFF?0:dist-er-mmrad-0.1);
    if(shot.wizid>=0)if(shot.action==ACTION_MAGIC_MISSILE&&!shot.self_rcdt){
      auto*p=final_mode?&final_wizacc:id2wizacc(shot.wizid);
      mm_target.wizid=shot.wizid;
      mm_target.beg=sp;
      mm_target.end=sp+(ep-sp).SetMag(self.getCastRange());
      mm_target.hp=shot.hp;
      mm_target.tick=0;
      mm_target.curhp=shot.hp;
      mm_target.beg_dist=dist;
      mm_target.target_cast_state=shot.target_cast_state;
    }
  }
  bool is_teamate(const Wizard&self,int player_id){
    auto&arr=getPlayers();
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      if(ex.getId()==player_id)return ex.getFaction()==self.getFaction();
    }
    return false;
  }
  int rem_tick_to_mob_gen(){int period=750;return period-(getTickIndex()%period);}
  int rem_tick_to_bon_gen(){int period=2500;return period-(getTickIndex()%period);}
  struct t_dir_timer{vec2d dir;int n;};
  PRO_FUNCGEN_GETP_BY_FIELD(const Wizard,id2wiz,getWizards(),int,getId());
  PRO_FUNCGEN_GETP_BY_FIELD(const Projectile,ownid2bullet,getProjectiles(),int,getOwnerUnitId());

  int get_low_hp_ewiz_id(const Wizard&self){
    auto arr=getWizards();auto sp=get_pos(self);auto dist=self.getVisionRange();
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      bool fail=self.getFaction()==ex.getFaction()||!sp.dist_to_point_less_that_r(get_pos(ex),dist);
      if(!fail)continue;
      ex.id=-1;
    }
    clean_if(arr,[](Wizard&ex){return ex.getId()<0;});
    auto id=QAP_MINVAL_ID_OF_VEC(arr,get_hp(ex));
    return id>=0?arr[id].getId():-1;
  }
  t_wizwall get_wizwall_in_point(const Wizard&wiz){
    t_wizwall out={get_pos(wiz),0,0,0,0};
    auto&arr=wizards;
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      if(ex.faction==wiz.faction)continue;
      if(!get_pos(ex).dist_to_point_less_that_r(out.center,pgame->wizardCastRange))continue;
      out.tn++;
      out.thp+=get_hp(ex);
      if(ex.remainingActionCooldownTicks)continue;
      if(ex.remainingCooldownTicksByAction[ACTION_MAGIC_MISSILE])continue;
      out.n++;
      out.hp+=get_hp(ex);
    }
    return out;
  }
  t_wizwall get_wizwall(const Wizard&self)
  {
    auto sp=get_pos(self);
    vector<t_wizwall> out;
    auto&arr=wizards;
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      if(ex.faction!=self.faction)continue;
      if(!get_pos(ex).dist_to_point_less_that_r(sp,pgame->wizardCastRange))continue;
      qap_add_back(out)=get_wizwall_in_point(ex);
    }
    int best_id=QAP_MINVAL_ID_OF_VEC(out,-ex.tn);
    if(best_id<0)
    {
      t_wizwall fail={get_pos(self),0,0,0,0};
      return fail;
    }
    auto&best=out[best_id];
    return best;
  }
  void move(const Wizard&self,const World&world,const Game&game,Move&move)
  {
    auto final_mode=game.rawMessagesEnabled;
    mmdmg=game.getMagicMissileDirectDamage();
    mmrad=game.getMagicMissileRadius();
    auto wh=vec2d(world.getWidth(),world.getHeight());
    auto cur_enemy_base_pos=enemy_main_tower.mid.get_pos();//wh-our_base_pos;
    auto sp=get_pos(self);auto sr=self.getRadius();auto smf=get_movfactor_with_timelimit(self);auto shp=get_hp(self);
    auto to_enemy_base=(cur_enemy_base_pos-sp).Norm();
    auto cur_our_base_pos=our_base_pos+((wh-our_base_pos)-our_base_pos).SetMag(std::max(0.0,(sp-our_base_pos).Rot(to_enemy_base).x-500));
    if(final_mode)cur_our_base_pos=our_base_pos;
    auto to_our_base=vec2d(cur_our_base_pos-sp).Norm();
    auto to_center=(wh*0.5-sp).Norm();

    load_units(getMinions());load_units(getWizards());update_forest(getTrees(),getTickIndex());
    
    g_low_hp_ewiz_id=get_low_hp_ewiz_id(self);
    if(final_mode&&g_low_hp_ewiz_id>0){
      //cur_enemy_base_pos=(wh-our_base_pos);
      //to_enemy_base=(cur_enemy_base_pos-sp).Norm();
    }

    move.setTurn(self.getAngleTo(cur_enemy_base_pos.x,cur_enemy_base_pos.y));
    
    auto&mm_target=*selfid2mmtarget(self.id);
    if(mm_target.wizid>=0)
    {
      auto&mt=mm_target;
      auto&acc=final_mode?final_wizacc:*id2wizacc(mt.wizid);
      auto*pewiz=id2wiz(mt.wizid);
      if(const Projectile*pbullet=ownid2bullet(self.getId()))
      {
        if(!pewiz){mt.reset();}
        if(pewiz){mt.curhp=get_hp(*pewiz);mm_target.tick++;}
      }else{
        if(!pewiz){
          acc.add_event(true,mt.target_cast_state);
        }
        if(pewiz){
          auto curhp=get_hp(*pewiz);
          auto oldhp=mt.curhp;
          auto dhp=curhp-oldhp;
          acc.add_event(dhp<0&&abs(dhp)>(mmdmg-2),mt.target_cast_state);
        }
        mt.reset();
      }
    }
    auto go_home=false;bool go_fast=false;
    bool go_home_from_tows=false;
    for(int i=0;i<enemy_tows.size();i++)
    {
      auto&tow=enemy_tows[i];
      update(tow,self);
      if(tow)
      {
        auto bfp=need_go_back(self,shp,smf,sp,sr,to_enemy_base,tow);
        if(bfp.go_back||bfp.go_panic)
        {
          go_home_from_tows=true;
        }
      }
    }
    real under_tow_hp_keof=enemy_main_tower.unlocked()?0.80:0.65;
    if(final_mode)under_tow_hp_keof=50.0/self.maxLife;
    auto&wizards=getWizards();
    auto near_wiz_index=QAP_MINVAL_ID_OF_VEC(wizards,get_pos(ex).sqr_dist_to(sp)+(self.faction==ex.faction?1e9:0));
    const auto&near_ewiz=wizards[near_wiz_index];
    bool is_near_ewiz_found=false;
    if(self.faction!=near_ewiz.faction)if(get_pos(near_ewiz).dist_to(sp)<self.visionRange*1.2)is_near_ewiz_found=true;
    if(!final_mode)if(is_near_ewiz_found)under_tow_hp_keof=0.9;
    if(self.getLife()<self.getMaxLife()*under_tow_hp_keof)go_home=go_home||(go_home_from_tows);
    bool go_from_bullet=false;
    auto&arr=world.getProjectiles();
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      //QapAssert(abs(Vec2dEx(ex.getAngle(),1).Rot(get_spd(ex)).y)<0.001);
      if(ex.getOwnerPlayerId()==self.getOwnerPlayerId())continue;
      if(is_teamate(self,ex.getOwnerPlayerId()))continue;
      auto sp_ox=(sp-get_pos(ex)).Rot(get_spd(ex));
      if(abs(sp_ox.y)<sr+mmrad)if(abs(sp_ox.x)<self.getCastRange()){go_home=true;go_from_bullet=true;if(shp<50)if(ex.getRadius()==mmrad)go_fast=true;}
    }
    
    //if(!final_mode||shp<=25)
    {
      auto rttmg=rem_tick_to_mob_gen();
      auto range=game.getWizardCastRange()*(final_mode?0.4:0.6);
      vec2d arr[]={vec2d(306,3146),vec2d(961,3962),vec2d(955,3174)};
      for(int i=0;i<3;i++)
      {
        auto ep=wh-arr[i];
        if((sp-to_enemy_base.SetMag(rttmg*2.9)).dist_to(ep)<range)go_home=true;
      }
    }
    {
      vec2d df=vec2d(0,0);int n=0;
      auto wiz_n=update_df(world.getWizards(),df,n,self);
      auto tow_n=update_df(world.getBuildings(),df,n,self);
      auto tre_n=update_df(world.getTrees(),df,n,self);
      auto bot_n=update_df(world.getMinions(),df,n,self);

      vec2d ox=Vec2dEx(self.getAngle(),1);
      auto dir=to_enemy_base;
      
      vector<t_shot> shots;
      
      auto this_flag_no_care_beacuse_of_see_handling__go_home_from_tows=(
        update_enemy_arr(shots,enemy_tows,self,game,move,dir)
      );
      t_go_back_result flags[]={
        update_enemy_arr(shots,world.getWizards(),self,game,move,dir),
        update_enemy_arr(shots,world.getMinions(),self,game,move,dir)
      };
      t_go_back_result bfp_sum={go_home,go_fast,false};
      for(int i=0;i<lenof(flags);i++)bfp_sum.add(flags[i]);
      for(int i=0;i<shots.size();i++){
        auto&ex=shots[i];
        ex.update_profit(sp,sr);
      }
      auto best_id=QAP_MINVAL_ID_OF_VEC(shots,-ex.profit);
      if(best_id>=0)for(;;)
      {
        auto&best=shots[best_id];
        if(final_mode)if(!bfp_sum.go_back)if(best.action!=ACTION_STAFF)if(best.ready)if(best.wizid>=0)break;
        if(try_haste(self,game,move))break;
        if(try_shield(self,game,move))break;
        do_shot(best,self,game,move,to_enemy_base);
        break;
      }
      if(final_mode)if(shp>16)if(is_near_ewiz_found)if(!go_from_bullet)
      {
        auto to_enemy=(wh-real_our_base_pos)-real_our_base_pos;
        auto fire_point=real_our_base_pos+to_enemy.SetMag(game.factionBaseRadius+self.radius*1.5+12.5*3.5);
        if((sp-fire_point).Rot(to_enemy).x<0){bfp_sum.go_back=false;bfp_sum.go_fast=false;}
      }
      bool ignore_go_back_because_of_wizwall=false;
      if(final_mode)if(real_enemy_base_pos.dist_to_point_less_that_r(sp,self.castRange))if(enemy_main_tower.unlocked())if(shp>16)
      {
        if(is_near_ewiz_found)
        {
          auto wall=get_wizwall(self);
          auto ewall=get_wizwall_in_point(near_ewiz);
          //if(wall.n>=2&&(real(wall.hp)/wall.n>24))ignore_go_back_because_of_wizwall=true;
          if(wall.tn>=2)if(wall.tn>=ewall.tn)if(wall.get_avr_thp()>ewall.get_avr_thp()+42)ignore_go_back_because_of_wizwall=true;
        }else ignore_go_back_because_of_wizwall=true;
      }
      if(ignore_go_back_because_of_wizwall){
        bfp_sum.go_back=false;bfp_sum.go_fast=false;
      }
      if(bfp_sum.go_back){dir=to_our_base;}
      if(!final_mode||shp<=12)if(bfp_sum.go_fast){move.setTurn(self.getAngleTo(sp.x+dir.x,sp.y+dir.y));}
      static t_dir_timer old_dir={to_enemy_base,128};
      if(is_almost_colinear(old_dir.dir,dir)){old_dir.n++;}else{old_dir.n=0;old_dir.dir=dir;};
      for(;;)
      {
        if(n==1)
        {
          auto df_dir=df.Rot(dir).Norm();
          if(df_dir.x<0)
          {
            df=df.SetMag(0.5)+df.Ort()*Sign(-df_dir.y);
            break;
          }
        }
        df+=dir;
        break;
      }
      auto df_ox=df.Rot(ox).Norm();
      set_move(game,self,move,df_ox);
      //move.setSpeed(fk*df_ox.x);
      //move.setStrafeSpeed(sk*df_ox.y);
      if(tre_n>0&&tre_n+tow_n==n)
      {
        auto&arr=world.getTrees();
        auto target=QAP_MINVAL_ID_OF_VEC(arr,get_pos(ex).dist_to(sp));
        if(target>=0)
        {
          auto ang=self.getAngleTo(arr[target]);
          move.setTurn(ang);
          move.setCastAngle(ang);
          move.setAction(world.getTickIndex()%60<30?ACTION_STAFF:ACTION_MAGIC_MISSILE);
          //move.setAction(ACTION_MAGIC_MISSILE);
          //if(self.getRemainingActionCooldownTicks())
          //move.setSpeed(0);
          //move.setStrafeSpeed(0);
        }else QapAssert(target>=0);
      }
    }
    auto max_turn_ticks=Pi/get_angspd(self);
    int gg=1;
  }
  static bool has_status(const Wizard&ref,StatusType type){bool already=false;QAP_FOREACH(ref.statuses,if(ex.type==type)already=true;);return already;}
  static real status_cast_range(){return Pi*0.95/12.0;}
  bool try_haste(const Wizard&self,const Game&game,Move&move)
  {
    auto sp=get_pos(self);
    if(self.mana<game.hasteManacost)return false;
    if(!qap_includes(self.skills,SKILL_HASTE))return false;
    if(self.remainingActionCooldownTicks)return false;
    if(self.remainingCooldownTicksByAction[ACTION_HASTE])return false;
    auto&arr=wizards;
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      if(ex.id==self.id)continue;
      if(ex.faction!=self.faction)continue;
      if(!get_pos(ex).dist_to_point_less_that_r(sp,game.wizardCastRange))continue;
      if(has_status(ex,STATUS_HASTENED))continue;
      auto angle=self.getAngleTo(ex);
      move.setTurn(angle);
      if(abs(angle)>status_cast_range())return true;
      move.setAction(ACTION_HASTE);
      move.setStatusTargetId(ex.id);
      move.setCastAngle(angle);
      move.setMinCastDistance(self.radius+5);
      move.setMaxCastDistance(+4000);
      return true;
    }
    return false;
  }
  bool try_shield(const Wizard&self,const Game&game,Move&move)
  {
    auto sp=get_pos(self);
    if(self.mana<game.shieldManacost)return false;
    if(!qap_includes(self.skills,SKILL_SHIELD))return false;
    if(self.remainingActionCooldownTicks)return false;
    if(self.remainingCooldownTicksByAction[ACTION_SHIELD])return false;
    auto&arr=wizards;
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      if(ex.id==self.id)continue;
      if(ex.faction!=self.faction)continue;
      if(ex.faction!=self.faction)continue;
      if(!get_pos(ex).dist_to_point_less_that_r(sp,game.wizardCastRange))continue;
      if(has_status(ex,STATUS_SHIELDED))continue;
      auto angle=self.getAngleTo(ex);
      move.setTurn(angle);
      if(abs(angle)>=status_cast_range())return true;
      move.setAction(ACTION_SHIELD);
      move.setStatusTargetId(ex.id);
      move.setCastAngle(angle);
      move.setMinCastDistance(self.radius+5);
      move.setMaxCastDistance(+4000);
      return true;
    }
    return false;
  }
  static bool is_almost_colinear(const vec2d&a,const vec2d&b){return a.Mag()>0.01&&abs(a.Rot(b).Norm().y)<0.01;}
};

vec2d clamp_movespeedinput(const Game&game,real speed,real strafe){
  auto sk=game.getWizardStrafeSpeed();
  auto fk=game.getWizardForwardSpeed();
  auto bk=game.getWizardBackwardSpeed();
  return vec2d(Clamp(speed,fk,bk),Clamp(strafe,-sk,+sk));
}

//real maxspd_go_back_time_to_

void MyStrategy::move(const Wizard& self, const World& world, const Game& game, Move& move) {
  auto sr=self.getRadius();
  auto angspd=game.getWizardMaxTurnAngle();
  auto attsec=game.getStaffSector();
  auto v=4/(Pi2*sr*2);
  auto mmspd=game.getMagicMissileSpeed();
  int ggg=1;
  /*
  auto tick=world.getTickIndex();
  //move.setTurn(self.getAngleTo(self.getX(),self.getY()+1000));
  int n=100;
  if(tick>=n){
    static const auto beg_pos=get_pos(self);
    auto sk=game.getWizardStrafeSpeed();
    auto fk=game.getWizardForwardSpeed();

    auto df_ox=vec2d(0,-1).Rot(Vec2dEx(self.getAngle(),1)).Norm();
    set_move(game,self,move,df_ox);
    //move.setTurn(-1000);
    auto sp=get_pos(self);
    // +6.1940176041876 in 30 frames = 0.2064672534729 per frame
    if(tick==n+15){
      real dist=sp.dist_to(beg_pos);//45
      int gg=1;
    }
    if(tick==n+30){
      real dist=sp.dist_to(beg_pos);//96.194017604187593*2
      int gg=1;
    }
    if(tick==n+60){
      real dist=sp.dist_to(beg_pos);
      int gg=1;
    }
  }
  auto r=self.getRadius();
  if(self.getStatuses().size()){
    int gg=1;
  };
  KB_CODE();
  return;
  */
  /*
  static bool need_log_trees=false;
  if(need_log_trees){
    string log;
    for(int i=0;i<id2tree.size();i++){
      auto&ex=id2tree[i];
      if(ex.tick<0)continue;
      log+=FToS(ex.pos.x)+","+FToS(ex.pos.y)+"\n";
    }
    int gg=1;
    string log2;
    vector<t_tree> tmp;auto&arr=world.getTrees();
    for(int i=0;i<arr.size();i++){
      auto&ex=arr[i];
      auto p=get_pos(ex);
      log2+=FToS(p.x)+","+FToS(p.y)+"\n";
    }
    int bgg=1;
    
    file_put_contents("forest1.txt",log);
    file_put_contents("forest2.txt",log2);
  }
  */
  static int debug_frame_id=4467;
  if(world.getTickIndex()==debug_frame_id){
    int gg=1;
  }
  if(!world.getTickIndex())
  {
    srand(game.getRandomSeed());
    auto wh=vec2d(world.getWidth(),world.getHeight());
    enemy_base_pos=wh-our_base_pos;
    auto&arr=world.getBuildings();
    for(int i=0;i<arr.size();i++)
    {
      auto&ex=arr[i];
      auto&b=qap_add_back(enemy_tows);
      //b.id=ex.getId();
      b.pos=wh-get_pos(ex);
      b.hp=ex.getLife();
      b.attrange=ex.getAttackRange();
      b.r=ex.getRadius();
      b.cdt=ex.getCooldownTicks();
      b.rcdt=ex.getRemainingActionCooldownTicks();
      b.dmg=ex.getDamage();
      b.faction=self.faction!=FACTION_ACADEMY?FACTION_ACADEMY:FACTION_RENEGADES;
      b.type=ex.type;
      if(ex.type==BUILDING_FACTION_BASE)real_enemy_base_pos=b.pos;
      if(ex.type==BUILDING_FACTION_BASE)real_our_base_pos=get_pos(ex);
    }
    auto center=wh*0.5;
    {
      auto&emt=enemy_main_tower;
      vector<int> useds(arr.size(),0);
      useds[QAP_MINVAL_ID_OF_VEC(enemy_tows,ex.pos.dist_to(real_enemy_base_pos))]=1;
      #define F(mid,law){auto id=QAP_MINVAL_ID_OF_VEC(enemy_tows,law+useds[i]*1e6);qap_add_back(emt.mid.arr)=&enemy_tows[id];useds[id]++;}
      F(mid,ex.pos.dist_to(center));
      F(low,-ex.pos.y);
      F(low,-ex.pos.x);
      F(top,+ex.pos.y);
      F(top,+ex.pos.x);
      #undef F
      QapAssert(arr.size()==6+1);
      qap_add_back(emt.mid.arr)=&enemy_tows[QAP_MINVAL_ID_OF_VEC(useds,ex)];
      int hoho=1;
    }
    int and_what_next=111;
  }
  pgame=&game;
  ((MeWorld&)world).move(self,world,game,move);
  if(game.rawMessagesEnabled)for(int i=0;i<world.wizards.size();i++){
    auto&ex=world.wizards[i];
    if(ex.me||ex.faction!=self.faction)continue;
    Move unused;
    ((MeWorld&)world).move(ex,world,game,unused);//just for fill mm_targets info
  }
  for(int i=0;i<enemy_tows.size();i++){auto&tow=enemy_tows[i];if(tow.rcdt)tow.rcdt--;}
  #ifdef Adler
  static bool hand_control=0;
  if(IsKeyDown(VK_LSHIFT))hand_control=!hand_control;
  if(hand_control)
  {
    //static int prev_tree=0;QapAssert(prev_tree<=world.getTrees().size());prev_tree=world.getTrees().size();
    auto staff_cdt=game.getStaffCooldownTicks();
    auto mm_cdt=game.getMagicMissileCooldownTicks();
    auto acdt=game.getWizardActionCooldownTicks();
    auto staff_dmg=game.getStaffDamage();
    auto mm_dmg=game.getMagicMissileDirectDamage();
    move.setSpeed(0);move.setTurn(0);move.setStrafeSpeed(0);
    move.setMinCastDistance(0);
    move.setAction(world.getTickIndex()%60<30?ACTION_STAFF:ACTION_MAGIC_MISSILE);
    //move.setAction(ACTION_STAFF);
  }
  #endif
  KB_CODE();
  auto mdbpsl=game.getMagicalDamageBonusPerSkillLevel();
  if(game.skillsEnabled)
  {
    /*
    RANGE_BONUS_PASSIVE
    RANGE_BONUS_AURA
    ADVANCED_MAGIC_MISSILE

    MAGICAL_DAMAGE_BONUS_PASSIVE
    MAGICAL_DAMAGE_BONUS_AURA
    FROST_BOLT

    STAFF_DAMAGE_BONUS_PASSIVE
    STAFF_DAMAGE_BONUS_AURA
    FIREBALL

    MOVEMENT_BONUS_FACTOR_PASSIVE
    MOVEMENT_BONUS_FACTOR_AURA
    HASTE

    MAGICAL_DAMAGE_ABSORPTION_PASSIVE
    MAGICAL_DAMAGE_ABSORPTION_AURA
    SHIELD
    */
    //vector<SkillType> log;for(int i=0;i<25;i++){
    SkillType ignore[]={
      _SKILL_COUNT_
      //SKILL_FROST_BOLT,
      //SKILL_FIREBALL
    };
    auto TO_MISSILE=SKILL_RANGE_BONUS_PASSIVE_1;
    auto TO_FROST_BOLT=SKILL_MAGICAL_DAMAGE_BONUS_PASSIVE_1;
    auto TO_FIREBALL=SKILL_STAFF_DAMAGE_BONUS_PASSIVE_1;
    auto TO_HASTE=SKILL_MOVEMENT_BONUS_FACTOR_PASSIVE_1;
    auto TO_SHIELD=SKILL_MAGICAL_DAMAGE_ABSORPTION_PASSIVE_1;

    SkillType id2firstskill[]={
      TO_FROST_BOLT,
      TO_FIREBALL,
      TO_MISSILE,
      TO_HASTE,
      TO_SHIELD
    };

    //SkillType id2firstskill[]={
    //  TO_HASTE,
    //  TO_FIREBALL,
    //  TO_MISSILE,
    //  TO_FIREBALL,
    //  TO_MISSILE
    //};

    auto next=[&ignore](SkillType last)->SkillType{
      auto tmp=SkillType((last+1)%_SKILL_COUNT_);
      for(int i=0;i<lenof(ignore);i++)if(ignore[i]==tmp)return SkillType(tmp+1);
      return tmp;
    };

    auto&arr=self.skills;//{auto arr=log;
    auto firstSkill=!game.rawMessagesEnabled?SKILL_RANGE_BONUS_PASSIVE_1:id2firstskill[(self.id-1)%5];//SkillType(SKILL_RANGE_BONUS_PASSIVE_1+5*((self.id-1)%5));
    auto skill=!arr.empty()?next(arr.back()):firstSkill;//SKILL_MOVEMENT_BONUS_FACTOR_PASSIVE_1
    move.setSkillToLearn(skill);
    //qap_add_back(log)=skill;}}
     int gg=1;
  }
}

MyStrategy::MyStrategy() { }
