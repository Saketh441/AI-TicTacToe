#ifndef DASHBOARD_H
#define DASHBOARD_H
 
#include <Arduino.h>
 
const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>Fingerprint-Based Electronic Voting Machine</title>
<style>
:root{--primary:#2563eb;--primary-light:#38bdf8;--primary-dark:#1e3a8a;--accent:#8b5cf6;--bg:#eef2ff;--card:rgba(255,255,255,.94);--text:#0f172a;--muted:#64748b;--line:rgba(148,163,184,.22);--green:#10b981;--red:#ef4444;--amber:#f59e0b;--info:#0ea5e9;--shadow:0 10px 40px rgba(15,23,42,.07);--shadow-lg:0 20px 50px rgba(37,99,235,.12);--glow-inset:0 0 0 1px rgba(255,255,255,.65) inset;--page-margin:10%;--shell-radius:24px;--font:'Segoe UI',system-ui,-apple-system,BlinkMacSystemFont,Roboto,'Helvetica Neue',Arial,sans-serif}
*{box-sizing:border-box}
html{scroll-behavior:smooth}
body{margin:0;font-family:var(--font);background:#030712;color:var(--text);min-height:100vh;-webkit-font-smoothing:antialiased;text-rendering:optimizeLegibility}
body::before{content:"";position:fixed;inset:0;background:radial-gradient(ellipse 80% 60% at 10% 15%,rgba(37,99,235,.45),transparent 50%),radial-gradient(ellipse 70% 50% at 90% 8%,rgba(34,211,238,.35),transparent 45%),radial-gradient(ellipse 60% 40% at 50% 95%,rgba(139,92,246,.28),transparent 50%),linear-gradient(160deg,#030712 0%,#0f172a 40%,#172554 100%);z-index:-2}
body::after{content:"";position:fixed;inset:0;background:url("data:image/svg+xml,%3Csvg viewBox='0 0 256 256' xmlns='http://www.w3.org/2000/svg'%3E%3Cfilter id='n'%3E%3CfeTurbulence type='fractalNoise' baseFrequency='0.9' numOctaves='4' stitchTiles='stitch'/%3E%3C/filter%3E%3Crect width='100%25' height='100%25' filter='url(%23n)' opacity='0.03'/%3E%3C/svg%3E");opacity:.4;pointer-events:none;z-index:-1}
.page-shell{padding:18px var(--page-margin);height:100vh;box-sizing:border-box}
.app{display:grid;grid-template-columns:272px 1fr;height:100%;overflow:hidden;border-radius:var(--shell-radius);box-shadow:0 30px 90px rgba(0,0,0,.45),0 0 0 1px rgba(255,255,255,.08),var(--glow-inset);background:rgba(255,255,255,.97);backdrop-filter:blur(24px) saturate(1.2);position:relative}
.app::before{content:"";position:absolute;inset:0;border-radius:inherit;background:linear-gradient(135deg,rgba(255,255,255,.4),transparent 40%);pointer-events:none;z-index:0}
.app>*{position:relative;z-index:1}
.sidebar{background:linear-gradient(165deg,#050a14 0%,#0c1222 40%,#111827 100%);color:#fff;padding:22px 18px;display:flex;flex-direction:column;height:100%;overflow:hidden;border-right:1px solid rgba(255,255,255,.06);position:relative}
.sidebar::before{content:"";position:absolute;top:0;left:0;right:0;height:4px;background:linear-gradient(90deg,#22d3ee,#2563eb,#7c3aed,#2563eb);background-size:200% 100%;animation:barShift 6s linear infinite}
@keyframes barShift{0%{background-position:0% 50%}100%{background-position:200% 50%}}
.brand{display:flex;align-items:center;gap:14px;margin-bottom:8px;padding:6px 4px}
.logo{width:54px;height:54px;border-radius:18px;background:linear-gradient(145deg,#38bdf8,#2563eb 50%,#4f46e5);display:grid;place-items:center;font-family:var(--font);font-size:.85rem;font-weight:700;letter-spacing:.02em;color:#fff;flex-shrink:0;box-shadow:0 12px 32px rgba(37,99,235,.5),inset 0 1px 0 rgba(255,255,255,.3);position:relative}
.logo::after{content:"";position:absolute;inset:-4px;border-radius:22px;border:2px solid rgba(56,189,248,.4);animation:logoRing 3s ease-in-out infinite}
@keyframes logoRing{0%,100%{opacity:.35;transform:scale(1)}50%{opacity:1;transform:scale(1.05)}}
.brand h1{font-family:var(--font);font-size:1.05rem;margin:0;line-height:1.2;font-weight:700;letter-spacing:0;color:#fff}
.brand p{margin:4px 0 0;color:#64748b;font-size:.72rem;line-height:1.4;font-weight:500;letter-spacing:.02em;text-transform:none}
.nav-label{font-size:.68rem;font-weight:600;letter-spacing:.06em;text-transform:uppercase;color:#475569;margin:18px 0 8px 12px}
.sidebar-nav{display:flex;flex-direction:column;gap:5px}
.sidebar-nav button{width:100%;display:flex;align-items:center;gap:11px;background:transparent;color:#94a3b8;border:1px solid transparent;border-radius:14px;padding:12px 14px;font-weight:600;font-size:.875rem;cursor:pointer;text-align:left;transition:all .28s cubic-bezier(.4,0,.2,1);position:relative;overflow:hidden}
.sidebar-nav button::before{content:"";position:absolute;left:0;top:50%;transform:translateY(-50%);width:3px;height:0;background:linear-gradient(180deg,#38bdf8,#2563eb);border-radius:0 4px 4px 0;transition:height .28s ease}
.sidebar-nav button:hover{color:#f1f5f9;background:rgba(255,255,255,.05);border-color:rgba(255,255,255,.06);padding-left:16px}
.sidebar-nav button.active{color:#fff;background:linear-gradient(135deg,rgba(37,99,235,.35),rgba(56,189,248,.12));border-color:rgba(96,165,250,.2);box-shadow:0 8px 28px rgba(37,99,235,.25),inset 0 1px 0 rgba(255,255,255,.08)}
.sidebar-nav button.active::before{height:60%}
.device-box{margin-top:auto;padding:16px 18px;border-radius:18px;background:linear-gradient(145deg,rgba(255,255,255,.07),rgba(255,255,255,.02));border:1px solid rgba(255,255,255,.08);color:#94a3b8;font-size:.74rem;line-height:1.8;backdrop-filter:blur(12px);box-shadow:inset 0 1px 0 rgba(255,255,255,.06)}
.device-box b{color:#e2e8f0;font-size:.78rem;letter-spacing:.06em;text-transform:uppercase;font-weight:700}
.dot{display:inline-block;width:7px;height:7px;border-radius:50%;background:var(--red);box-shadow:0 0 14px rgba(239,68,68,.7);vertical-align:middle;margin-left:5px;animation:dotPulse 2s infinite}
.dot.ok{background:var(--green);box-shadow:0 0 14px rgba(16,185,129,.7)}
@keyframes dotPulse{0%,100%{opacity:1;transform:scale(1)}50%{opacity:.5;transform:scale(.85)}}
.main{padding:22px 28px 24px;min-width:0;overflow:hidden;display:flex;flex-direction:column;height:100%;background:linear-gradient(180deg,#fafbff 0%,#f1f5f9 100%);position:relative}
.main::before{content:"";position:absolute;inset:0;background-image:radial-gradient(circle at 1px 1px,rgba(148,163,184,.12) 1px,transparent 0);background-size:24px 24px;pointer-events:none;opacity:.5}
.main>*{position:relative;z-index:1}
.topbar{display:flex;align-items:center;justify-content:space-between;gap:16px;margin-bottom:18px;flex-wrap:wrap;flex-shrink:0;padding:14px 18px;background:rgba(255,255,255,.72);border:1px solid var(--line);border-radius:18px;box-shadow:var(--shadow);backdrop-filter:blur(12px)}
.topbar h2{margin:0;font-family:var(--font);font-size:1.35rem;letter-spacing:0;font-weight:700;color:var(--text)}
.topbar p{margin:5px 0 0;color:var(--muted);font-size:.84rem;max-width:640px;line-height:1.45;font-weight:500}
.live-pill{display:inline-flex;align-items:center;gap:6px;font-size:.7rem;font-weight:600;text-transform:none;letter-spacing:0;color:#059669;background:linear-gradient(135deg,#ecfdf5,#d1fae5);padding:4px 10px;border-radius:999px;margin-bottom:6px;border:1px solid #a7f3d0}
.live-dot{width:6px;height:6px;border-radius:50%;background:#10b981;box-shadow:0 0 10px #10b981;animation:dotPulse 1.5s infinite}
.topbar-actions{display:flex;gap:10px;flex-wrap:wrap;align-items:center}
.topbar-actions .btn{padding:10px 16px;font-size:.8rem;border-radius:999px}
.page{display:none;flex:1;min-height:0;overflow-y:auto}
.page.active{display:block}
.page.dash-page.active{display:flex;flex-direction:column;overflow:hidden}
.main.dash-view .topbar{margin-bottom:12px;padding-bottom:10px}
.main.dash-view .topbar h2{font-size:1.25rem}
.main.dash-view .topbar p{display:none}
.main.dash-view{padding:16px 22px 18px}
.card{background:var(--card);border:1px solid var(--line);border-radius:20px;box-shadow:var(--shadow);overflow:hidden;height:100%;display:flex;flex-direction:column;backdrop-filter:blur(16px);transition:transform .3s ease,box-shadow .3s ease}
.panel-card:hover{box-shadow:var(--shadow-lg);transform:translateY(-2px)}
.dash-page .panel-card:hover{transform:none}
.card-header{background:linear-gradient(125deg,#1d4ed8 0%,#2563eb 35%,#0891b2 70%,#06b6d4 100%);color:#fff;padding:14px 20px;font-weight:700;border:none;display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap;position:relative;overflow:hidden}
.card-header::before{content:"";position:absolute;inset:0;background:linear-gradient(90deg,transparent,rgba(255,255,255,.08),transparent);transform:translateX(-100%);animation:headerShine 4s ease-in-out infinite}
@keyframes headerShine{0%,100%{transform:translateX(-100%)}50%{transform:translateX(100%)}}
.card-header::after{content:"";position:absolute;top:-50%;right:-5%;width:140px;height:140px;background:radial-gradient(circle,rgba(255,255,255,.2),transparent 65%);pointer-events:none}
.card-header-title{white-space:nowrap;position:relative;z-index:1;letter-spacing:0;font-family:var(--font);font-size:.95rem;font-weight:600}
.card-header-meta{font-size:.72rem;font-weight:600;white-space:nowrap;position:relative;z-index:1;background:rgba(255,255,255,.15);padding:5px 12px;border-radius:999px;border:1px solid rgba(255,255,255,.2);backdrop-filter:blur(4px)}
.card-body{padding:20px;flex:1}
.stat-card{text-align:left;padding:18px;position:relative;overflow:hidden;border:1px solid var(--line)!important;background:linear-gradient(160deg,rgba(255,255,255,.98),rgba(248,250,252,.9))!important}
.stat-card::before{content:"";position:absolute;top:-40px;right:-40px;width:110px;height:110px;border-radius:50%;background:radial-gradient(circle,rgba(37,99,235,.1),transparent 70%);pointer-events:none}
.stat-card .stat-icon{width:44px;height:44px;border-radius:14px;display:grid;place-items:center;font-size:1.2rem;margin-bottom:12px;background:#f8fafc;box-shadow:0 6px 16px rgba(15,23,42,.08),inset 0 1px 0 rgba(255,255,255,.8)}
.stat-card .value{word-break:break-word;font-size:1.9rem;font-weight:700;color:var(--text);line-height:1;font-variant-numeric:tabular-nums;letter-spacing:0}
.stat-card .label{font-size:.68rem;text-transform:uppercase;letter-spacing:.05em;color:var(--muted);font-weight:600;margin-bottom:8px}
.dash-stats .stat-card{text-align:center;padding:16px 14px;transition:transform .25s cubic-bezier(.4,0,.2,1),box-shadow .25s ease}
.dash-stats .stat-card:hover{transform:translateY(-4px);box-shadow:var(--shadow-lg)}
.dash-stats .stat-card .stat-icon{margin:0 auto 12px}
.dash-stats .stat-card.stat-accent-1 .stat-icon{background:linear-gradient(145deg,#dbeafe,#93c5fd);color:#1e40af;box-shadow:0 6px 20px rgba(37,99,235,.2)}
.dash-stats .stat-card.stat-accent-2 .stat-icon{background:linear-gradient(145deg,#d1fae5,#6ee7b7);color:#047857;box-shadow:0 6px 20px rgba(16,185,129,.2)}
.dash-stats .stat-card.stat-accent-3 .stat-icon{background:linear-gradient(145deg,#fef3c7,#fcd34d);color:#b45309;box-shadow:0 6px 20px rgba(245,158,11,.2)}
.dash-stats .stat-card.stat-accent-4 .stat-icon{background:linear-gradient(145deg,#ede9fe,#c4b5fd);color:#6d28d9;box-shadow:0 6px 20px rgba(139,92,246,.2)}
.dash-stats .stat-card{padding:16px 14px;border:none!important;box-shadow:var(--shadow)!important}
.dash-stats .stat-card.stat-accent-1{box-shadow:0 8px 30px rgba(59,130,246,.12)!important}.dash-stats .stat-card.stat-accent-2{box-shadow:0 8px 30px rgba(16,185,129,.1)!important}.dash-stats .stat-card.stat-accent-3{box-shadow:0 8px 30px rgba(245,158,11,.1)!important}.dash-stats .stat-card.stat-accent-4{box-shadow:0 8px 30px rgba(139,92,246,.1)!important}
.dash-stats .stat-card .value{font-size:1.6rem!important}
.dash-stats .stat-card .label{font-size:.62rem;margin-bottom:4px}
.winner-banner{background:linear-gradient(135deg,rgba(236,253,245,.98),rgba(167,243,208,.85));border:1px solid rgba(110,231,183,.6);border-radius:20px;padding:15px 22px;margin-bottom:16px;color:#064e3b;font-weight:700;font-size:.9rem;line-height:1.45;flex-shrink:0;display:flex;align-items:center;gap:14px;box-shadow:0 12px 36px rgba(16,185,129,.18),inset 0 1px 0 rgba(255,255,255,.6);position:relative;overflow:hidden}
.winner-banner::before{content:"";position:absolute;inset:0;background:linear-gradient(90deg,transparent,rgba(255,255,255,.35),transparent);transform:translateX(-100%);animation:headerShine 5s ease-in-out infinite;pointer-events:none}
.winner-banner.empty{background:rgba(255,255,255,.85);border-color:var(--line);color:var(--muted);box-shadow:var(--shadow);font-weight:600}
.winner-banner.empty::before{display:none}
.winner-banner .banner-icon{font-size:1.5rem;flex-shrink:0;filter:drop-shadow(0 2px 6px rgba(16,185,129,.3));position:relative;z-index:1}
.winner-banner>span{position:relative;z-index:1}
.dash-page .row{gap:14px;margin-bottom:14px}
.dash-stats{margin-bottom:12px!important}
.dash-stats .stat-card .sub{display:none}
.dash-split{display:grid;grid-template-columns:3fr 2fr;gap:16px;flex:1;min-height:0}
.dash-split>.card{min-height:0}
.dash-split .dash-votes .card-body{display:flex;flex-direction:column;min-height:0;padding:16px 18px;overflow:hidden;background:linear-gradient(180deg,#fafbff,#f8fafc)}
.dash-split .card-body{padding:16px 18px;overflow-y:auto}
.dash-split .card-header{padding:12px 18px;font-size:.92rem}
#voteDistributionPanel,#liveResultsPanel{display:flex;flex-direction:column;gap:12px;flex:1;min-height:0}
.candidate-row{padding:15px 18px;border-radius:16px;border:1px solid var(--line);background:rgba(255,255,255,.88);box-shadow:0 4px 16px rgba(15,23,42,.04);transition:all .28s cubic-bezier(.4,0,.2,1);border-left:5px solid transparent;backdrop-filter:blur(8px)}
.candidate-row:hover{transform:translateY(-2px);box-shadow:0 12px 32px rgba(15,23,42,.1)}
.candidate-row.cand-0{border-left-color:#3b82f6}.candidate-row.cand-1{border-left-color:#10b981}.candidate-row.cand-2{border-left-color:#06b6d4}.candidate-row.cand-3{border-left-color:#f59e0b}
.candidate-row.leading{background:linear-gradient(135deg,rgba(240,253,244,.98),rgba(209,250,229,.6));border-color:rgba(134,239,172,.8);box-shadow:0 12px 36px rgba(16,185,129,.18)}
.candidate-main{display:flex;align-items:center;gap:12px;margin-bottom:10px}
.cand-badge{width:36px;height:36px;border-radius:12px;display:grid;place-items:center;font-size:.82rem;font-weight:800;color:#fff;flex-shrink:0;box-shadow:0 6px 16px rgba(0,0,0,.18)}
.candidate-row.cand-0 .cand-badge{background:linear-gradient(145deg,#60a5fa,#1d4ed8)}
.candidate-row.cand-1 .cand-badge{background:linear-gradient(145deg,#34d399,#047857)}
.candidate-row.cand-2 .cand-badge{background:linear-gradient(145deg,#22d3ee,#0e7490)}
.candidate-row.cand-3 .cand-badge{background:linear-gradient(145deg,#fbbf24,#b45309)}
.candidate-name{display:block;font-weight:600;font-size:.9rem;color:var(--text);line-height:1.3;letter-spacing:0;font-family:var(--font)}
.candidate-meta{display:block;font-size:.74rem;color:var(--muted);margin-top:3px;font-weight:600}
.cand-lead-tag{font-size:.6rem;font-weight:800;text-transform:uppercase;letter-spacing:.08em;padding:6px 11px;border-radius:999px;background:linear-gradient(135deg,#bbf7d0,#86efac);color:#065f46;flex-shrink:0;box-shadow:0 4px 12px rgba(16,185,129,.25)}
.progress{height:12px;background:linear-gradient(180deg,#e2e8f0,#f1f5f9);border-radius:999px;overflow:hidden;width:100%;box-shadow:inset 0 2px 4px rgba(15,23,42,.08)}
.progress-bar{height:100%;border-radius:999px;position:relative;overflow:hidden;min-width:0;transition:width .6s cubic-bezier(.34,1.2,.64,1);box-shadow:0 0 20px rgba(37,99,235,.35)}
.progress-bar:not(.empty)::after{content:"";position:absolute;inset:0;background:linear-gradient(90deg,transparent,rgba(255,255,255,.45),transparent);animation:shimmer 2.5s ease-in-out infinite}
@keyframes shimmer{0%{transform:translateX(-100%)}100%{transform:translateX(100%)}}
.progress-bar.empty{width:0!important;box-shadow:none}
.bar-0{background:linear-gradient(90deg,#60a5fa,#2563eb)}.bar-1{background:linear-gradient(90deg,#34d399,#059669)}.bar-2{background:linear-gradient(90deg,#22d3ee,#0891b2)}.bar-3{background:linear-gradient(90deg,#fbbf24,#d97706)}
.dash-feed .table-wrap{max-height:none;flex:1;min-height:0;overflow-y:auto;background:#fff}
.dash-feed .card-body{display:flex;flex-direction:column;min-height:0;padding:0;background:linear-gradient(180deg,#fafbff,#fff)}
.dash-feed table{min-width:0;width:100%;table-layout:fixed}
.dash-feed th,.dash-feed td{padding:9px 12px;font-size:.76rem;word-break:break-word}
.dash-feed th{font-size:.67rem;text-transform:uppercase;letter-spacing:.06em;font-weight:700;color:#64748b}
.dash-feed th:nth-child(1),.dash-feed td:nth-child(1){width:28%}
.dash-feed th:nth-child(2),.dash-feed td:nth-child(2){width:22%}
.dash-feed thead th{position:sticky;top:0;z-index:1;background:#f8fafc;border-bottom:2px solid var(--line)}
.dash-feed tbody tr{transition:background .15s ease}
.dash-feed tbody tr:hover{background:#eff6ff}
.dash-feed tbody tr:nth-child(even){background:#f8fafc}
.dash-feed-footer{padding:10px 14px;font-size:.72rem;color:var(--muted);border-top:1px solid var(--line);flex-shrink:0;background:#fff;font-weight:500}
.row{display:grid;grid-template-columns:repeat(12,minmax(0,1fr));gap:16px;margin-bottom:16px;align-items:stretch}
.col-3{grid-column:span 3}.col-4{grid-column:span 4}.col-6{grid-column:span 6}.col-8{grid-column:span 8}.col-12{grid-column:span 12}
.row>[class*="col-"]{min-width:0}
.candidate-info{flex:1;min-width:0}
.candidate-head{display:flex;justify-content:space-between;align-items:center;gap:8px;margin-bottom:2px}
.candidate-votes{font-weight:700;color:var(--primary);font-size:.78rem}
.welcome-card{background:linear-gradient(135deg,#fff,#f8fbff);border-radius:20px;padding:22px 24px;margin-bottom:20px;box-shadow:var(--shadow);border:1px solid rgba(37,99,235,.08)}
.btn{border:0;border-radius:999px;padding:11px 20px;font-weight:600;cursor:pointer;display:inline-flex;align-items:center;justify-content:center;gap:6px;font-family:var(--font);font-size:.875rem;transition:all .25s cubic-bezier(.4,0,.2,1);letter-spacing:0;position:relative;overflow:hidden}
.btn::after{content:"";position:absolute;inset:0;background:linear-gradient(180deg,rgba(255,255,255,.12),transparent);pointer-events:none}
.btn:hover{transform:translateY(-2px);filter:brightness(1.06)}
.btn:active{transform:translateY(0) scale(.98)}
.btn-primary{background:linear-gradient(135deg,#2563eb,#0891b2);color:#fff;box-shadow:0 10px 28px rgba(37,99,235,.35)}
.btn-success{background:linear-gradient(135deg,#10b981,#059669);color:#fff;box-shadow:0 10px 28px rgba(16,185,129,.3)}
.btn-danger{background:linear-gradient(135deg,#f87171,#dc2626);color:#fff;box-shadow:0 10px 28px rgba(239,68,68,.3)}
.btn-light{background:rgba(255,255,255,.95);color:var(--text);border:1px solid var(--line);box-shadow:0 4px 14px rgba(15,23,42,.06)}
.btn-sm{padding:8px 14px;font-size:.78rem}
.badge{display:inline-flex;padding:5px 11px;border-radius:999px;font-size:.7rem;font-weight:700;letter-spacing:.02em;box-shadow:0 2px 6px rgba(0,0,0,.06)}
.b-vote{background:linear-gradient(135deg,#d1fae5,#a7f3d0);color:#065f46}.b-already{background:linear-gradient(135deg,#fee2e2,#fecaca);color:#991b1b}.b-vote-pending{background:linear-gradient(135deg,#fef3c7,#fde68a);color:#92400e}.b-enrolled{background:linear-gradient(135deg,#ede9fe,#ddd6fe);color:#5b21b6}.b-error{background:linear-gradient(135deg,#fee2e2,#fecaca);color:#991b1b}.b-info{background:linear-gradient(135deg,#e0f2fe,#bae6fd);color:#075985}
input,select,textarea{width:100%;border:2px solid var(--line);border-radius:12px;padding:12px 14px;font-size:.92rem;outline:none;background:rgba(255,255,255,.95);font-family:var(--font);transition:border-color .2s ease,box-shadow .2s ease}
input:focus,select:focus,textarea:focus{border-color:#60a5fa;box-shadow:0 0 0 4px rgba(37,99,235,.12)}
.form-group label{display:block;font-size:.75rem;text-transform:none;letter-spacing:0;color:var(--muted);font-weight:600;margin-bottom:7px}
.fingerprint-scan{width:80px;height:80px;border:3px solid transparent;border-radius:50%;margin:0 auto 14px;position:relative;background:linear-gradient(#fff,#fff) padding-box,linear-gradient(135deg,#22d3ee,#2563eb) border-box;box-shadow:0 0 30px rgba(37,99,235,.35);animation:pulse 2s infinite}
.fingerprint-scan::before{content:"👆";position:absolute;inset:0;display:grid;place-items:center;font-size:1.6rem;opacity:.85}
.fingerprint-scan::after{content:"";position:absolute;width:55%;height:2px;background:linear-gradient(90deg,transparent,#2563eb,transparent);top:50%;left:22%;animation:scan 2.2s infinite linear}
@keyframes scan{0%{transform:translateY(-32px);opacity:0}50%{opacity:1}100%{transform:translateY(32px);opacity:0}}
@keyframes pulse{0%,100%{box-shadow:0 0 20px rgba(37,99,235,.25)}50%{box-shadow:0 0 35px rgba(34,211,238,.55)}}
th,td{padding:12px 16px;border-bottom:1px solid var(--line);text-align:left;font-size:.88rem}
th{background:#f8fafc;color:var(--muted);font-weight:700;border-top:none;text-transform:uppercase;font-size:.72rem;letter-spacing:.05em}
tbody tr{transition:background .15s ease}
tbody tr:hover{background:#eff6ff}
.reg-side{text-align:center;padding:22px 18px;background:linear-gradient(165deg,rgba(248,250,252,.95),rgba(239,246,255,.9));border:1px solid var(--line);border-radius:20px;box-shadow:inset 0 1px 0 rgba(255,255,255,.9),0 8px 24px rgba(37,99,235,.06)}
.reg-step{padding:9px 14px;border-radius:999px;background:rgba(255,255,255,.8);border:1px solid var(--line);font-size:.78rem;font-weight:700;color:var(--muted);transition:all .2s ease}
.reg-step.active{background:linear-gradient(135deg,#dbeafe,#e0f2fe);border-color:#93c5fd;color:#1d4ed8;box-shadow:0 4px 12px rgba(37,99,235,.15)}
.reg-step.done{background:linear-gradient(135deg,#d1fae5,#ecfdf5);border-color:#86efac;color:#047857}
.live-modal{position:fixed;inset:0;z-index:1000;display:none;align-items:center;justify-content:center;padding:22px;background:rgba(3,7,18,.65);backdrop-filter:blur(16px) saturate(1.2)}
.live-modal.show{display:flex;animation:fadeIn .25s ease}
@keyframes fadeIn{from{opacity:0}to{opacity:1}}
.live-card{width:min(540px,96vw);background:rgba(255,255,255,.98);border-radius:28px;box-shadow:0 30px 90px rgba(0,0,0,.35);padding:32px 34px;text-align:center;border:none;animation:popIn .4s cubic-bezier(.34,1.4,.64,1);backdrop-filter:blur(20px);position:relative;overflow:hidden}
.live-card::before{content:"";position:absolute;top:0;left:0;right:0;height:5px;background:linear-gradient(90deg,#2563eb,#06b6d4,#8b5cf6)}
@keyframes popIn{from{opacity:0;transform:scale(.9) translateY(16px)}to{opacity:1;transform:scale(1) translateY(0)}}
.live-card h2{font-family:var(--font);font-weight:700;letter-spacing:0}
.banner{position:fixed;right:22px;top:22px;z-index:1001;width:min(420px,calc(100vw - 44px));display:none;background:rgba(255,255,255,.97);border-radius:18px;border:none;box-shadow:0 20px 50px rgba(15,23,42,.2);padding:18px 20px 18px 24px;backdrop-filter:blur(16px);animation:slideIn .4s cubic-bezier(.34,1.3,.64,1);overflow:hidden}
.banner::before{content:"";position:absolute;left:0;top:0;bottom:0;width:5px;background:linear-gradient(180deg,#2563eb,#06b6d4)}
.banner.success::before{background:linear-gradient(180deg,#10b981,#059669)}.banner.error::before{background:linear-gradient(180deg,#ef4444,#dc2626)}.banner.info::before{background:linear-gradient(180deg,#0ea5e9,#2563eb)}
.banner.show{display:block}.banner.success,.banner.error,.banner.info{border-left:none}
::-webkit-scrollbar{width:7px;height:7px}
::-webkit-scrollbar-track{background:transparent}
::-webkit-scrollbar-thumb{background:linear-gradient(180deg,#cbd5e1,#94a3b8);border-radius:999px}
.stat-card .sub{font-size:.72rem;color:var(--muted);margin-top:4px}
.modal-icon{width:68px;height:68px;border-radius:50%;display:grid;place-items:center;font-size:1.75rem;margin:0 auto 18px;font-weight:800;line-height:1;box-shadow:0 10px 28px rgba(0,0,0,.1)}
.modal-icon.success{background:linear-gradient(135deg,#dcfce7,#bbf7d0);color:#15803d}
.modal-icon.error{background:linear-gradient(135deg,#fee2e2,#fecaca);color:#b91c1c}
.modal-icon.info{background:linear-gradient(135deg,#dbeafe,#bfdbfe);color:#1d4ed8}
.modal-icon.warning{background:linear-gradient(135deg,#fef3c7,#fde68a);color:#b45309}
.live-card.modal-success{border-top-color:var(--green)}.live-card.modal-error{border-top-color:var(--red)}.live-card.modal-info{border-top-color:var(--info)}.live-card.modal-warning{border-top-color:var(--amber)}
.live-card h2{margin:0 0 8px;font-size:1.25rem;color:var(--text)}
.live-card p{color:var(--muted);line-height:1.55;margin:0 0 16px;font-size:.92rem;font-weight:500}
.detail-grid{display:grid;grid-template-columns:1fr 1fr;gap:10px;margin-top:4px;text-align:left}
.detail.hidden{display:none}
.detail span{display:block;color:var(--muted);font-size:.7rem;text-transform:uppercase;font-weight:700;margin-bottom:4px;letter-spacing:.05em}
.detail strong{display:block;font-size:.92rem;color:var(--text);word-break:break-word;font-weight:700}
.status-badge{display:inline-flex;padding:5px 10px;border-radius:999px;font-size:.76rem;font-weight:700;background:#f1f5f9;color:var(--muted)}
.status-badge.ok{background:linear-gradient(135deg,#d1fae5,#a7f3d0);color:#047857}.status-badge.bad{background:linear-gradient(135deg,#fee2e2,#fecaca);color:#991b1b}
.form-group{margin-bottom:14px}
textarea{min-height:72px;resize:vertical}
.form-grid{display:grid;grid-template-columns:1fr 1fr;gap:14px}
.form-grid .full{grid-column:span 2}
.table-wrap{overflow-x:auto;overflow-y:auto;max-height:420px;-webkit-overflow-scrolling:touch}
table{width:100%;border-collapse:collapse;min-width:640px;table-layout:auto}
.progress-table .progress{min-width:120px}
tr.leading-row td{background:#f0fdf4}
.welcome-card h2{margin:0 0 6px;font-size:1.35rem;color:var(--text);font-weight:700}
.welcome-card p{margin:0;color:var(--muted);line-height:1.5;max-width:900px}
.panel-card{transition:transform .25s ease,box-shadow .25s ease}
.sensor-note{background:linear-gradient(135deg,#eff6ff,#dbeafe);border:1px solid #bfdbfe;border-radius:14px;padding:12px 16px;margin-bottom:14px;font-size:.88rem;color:#1e3a8a}
.toolbar{display:flex;gap:10px;flex-wrap:wrap;margin-bottom:16px}
.register-warning{display:none;background:linear-gradient(135deg,#fffbeb,#fef3c7);border:1px solid #fde68a;color:#92400e;padding:11px 14px;border-radius:12px;margin:12px 0 0;font-size:.88rem;font-weight:600}
.register-warning.show{display:block}
.register-steps{display:flex;gap:8px;flex-wrap:wrap;margin-bottom:16px}
.vote-activity-item{padding:11px 14px;border-left:4px solid transparent;border-radius:12px;margin-bottom:8px;background:rgba(248,250,252,.9);transition:all .28s ease;font-size:.86rem;line-height:1.45;word-break:break-word;border:1px solid var(--line);border-left-width:4px}
.vote-activity-item:hover{background:#eff6ff;border-left-color:var(--primary);transform:translateX(3px);box-shadow:0 4px 16px rgba(37,99,235,.08)}
.actions-grid{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:14px}
.action-tile{text-align:center;padding:22px 16px;cursor:pointer;border:1px solid var(--line);border-radius:18px;background:rgba(255,255,255,.92);transition:all .28s cubic-bezier(.4,0,.2,1);height:100%;backdrop-filter:blur(8px)}
.action-tile:hover{transform:translateY(-3px);box-shadow:0 14px 32px rgba(15,23,42,.1);border-color:rgba(37,99,235,.2)}
.action-icon{font-size:1.9rem;margin-bottom:10px;line-height:1;filter:drop-shadow(0 2px 8px rgba(0,0,0,.08))}
.action-tile h4{margin:0 0 6px;font-size:.95rem;font-family:var(--font);font-weight:600}
.action-tile p{margin:0;color:var(--muted);font-size:.82rem;line-height:1.4;min-height:2.8em}
.action-tile .btn-go{margin-top:12px;background:linear-gradient(135deg,var(--primary),var(--primary-light));color:#fff;border:0;border-radius:999px;padding:9px 16px;font-weight:700;cursor:pointer;font-size:.82rem;width:100%;max-width:180px;pointer-events:none;box-shadow:0 6px 18px rgba(37,99,235,.25)}
.action-tile.danger .btn-go{background:linear-gradient(135deg,#f87171,var(--red))}
.detail{border:1px solid var(--line);background:linear-gradient(180deg,#fff,#f8fafc);border-radius:14px;padding:11px 13px;transition:transform .15s ease}
.detail:hover{transform:translateY(-1px)}
@keyframes slideIn{from{opacity:0;transform:translateX(24px)}to{opacity:1;transform:translateX(0)}}
.results-toolbar-meta{font-size:.78rem;color:var(--muted);font-weight:600;background:rgba(255,255,255,.7);padding:6px 12px;border-radius:999px;border:1px solid var(--line)}
.page.active{animation:pageIn .35s ease}
@keyframes pageIn{from{opacity:0;transform:translateY(6px)}to{opacity:1;transform:translateY(0)}}
.reg-stats .stat-card{padding:12px 10px;text-align:center;border-top:3px solid transparent;transition:transform .2s ease}
.reg-stats .stat-card:hover{transform:translateY(-3px)}
.reg-stats .stat-card .stat-icon{width:32px;height:32px;border-radius:9px;display:grid;place-items:center;font-size:1rem;margin:0 auto 8px;background:#f1f5f9}
.reg-stats .stat-card.stat-accent-1{border-top-color:#3b82f6}.reg-stats .stat-card.stat-accent-1 .stat-icon{background:#dbeafe;color:#1d4ed8}
.reg-stats .stat-card.stat-accent-2{border-top-color:#22c55e}.reg-stats .stat-card.stat-accent-2 .stat-icon{background:#dcfce7;color:#15803d}
.reg-stats .stat-card.stat-accent-3{border-top-color:#f59e0b}.reg-stats .stat-card.stat-accent-3 .stat-icon{background:#fef3c7;color:#b45309}
.reg-stats .stat-card.stat-accent-4{border-top-color:#8b5cf6}.reg-stats .stat-card.stat-accent-4 .stat-icon{background:#ede9fe;color:#6d28d9}
.reg-stats .stat-card .value{font-size:1.5rem}
.reg-stats .stat-card .label{font-size:.65rem}
.reg-side .register-steps{flex-direction:column;align-items:stretch;margin-bottom:0}
.reg-side .reg-step{text-align:center}
.reg-card .card-body{padding:20px 22px}
.reg-layout{display:grid;grid-template-columns:220px 1fr;gap:22px;align-items:start}
.reg-side .fingerprint-scan{margin:0 auto 14px}
.reg-hint{font-size:.82rem;color:var(--muted);margin:6px 0 14px;line-height:1.45}
.reg-form-wrap{min-width:0}
.reg-toolbar{margin-top:4px;padding-top:4px}
.reg-page .row{margin-bottom:12px}
.results-toolbar{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap;margin-bottom:14px}
.results-toolbar .toolbar{margin-bottom:0}
.res-page .dash-split{margin-bottom:14px}
.res-results-card{margin-bottom:14px}
.res-results-card .card-body{background:linear-gradient(180deg,#fafbff,#f8fafc);padding:16px 18px}
.res-history-card{margin-top:0}
.res-history-card .card-body{padding:0}
.res-history-card .table-wrap{max-height:360px}
.res-history-card th,.res-history-card td{font-size:.82rem;padding:10px 12px}
.res-history-card tbody tr:nth-child(even){background:#f8fafc}
.res-page .progress-table .card-body{padding:14px 16px;background:#fafbfc}
.records-page .row{margin-bottom:12px}
.records-card .card-body{padding:0}
.records-card .table-wrap{max-height:480px}
.records-card th,.records-card td{font-size:.82rem;padding:10px 12px}
.records-card tbody tr:nth-child(even){background:#f8fafc}
.records-card tbody tr{transition:background .15s ease}
.records-card tbody tr:hover{background:#eff6ff}
.records-card thead th{position:sticky;top:0;z-index:1;background:#f8fafc}
.main.dash-view .live-pill{display:none}
@media(max-height:760px){.page-shell{padding:10px 8%}.main.dash-view{padding:12px 16px 14px}.main.dash-view .topbar h2{font-size:1.1rem}.dash-stats .stat-card{padding:10px 8px}.dash-stats .stat-card .value{font-size:1.3rem!important}.winner-banner{padding:8px 12px;font-size:.8rem;margin-bottom:8px}.dash-split .card-header{padding:9px 12px}.dash-split .card-body{padding:10px 12px}.candidate-row{padding:8px 10px}.progress{height:8px}.dash-feed th,.dash-feed td{padding:6px 8px;font-size:.7rem}}
@media(max-width:992px){:root{--page-margin:5%}.page-shell{padding:10px var(--page-margin);height:auto;min-height:100vh}.app{grid-template-columns:1fr;height:auto;min-height:calc(100vh - 20px);overflow:visible;border-radius:14px}.main{height:auto;overflow:visible}.page.dash-page.active{display:block;overflow:visible}.dash-split{grid-template-columns:1fr}.dash-votes .card-body{overflow-y:auto}.sidebar{position:sticky;top:0;z-index:50;padding:16px;height:auto;overflow:visible}.sidebar-nav{flex-direction:row;flex-wrap:wrap}.sidebar-nav button{width:auto;flex:1 1 calc(50% - 4px);justify-content:center;font-size:.82rem;padding:10px 8px}.device-box{margin-top:12px}.col-3,.col-4,.col-6,.col-8{grid-column:span 12}.actions-grid{grid-template-columns:1fr}}
@media(max-width:560px){:root{--page-margin:3%}.main{padding:14px 12px 24px}.topbar{flex-direction:column}.topbar-actions{width:100%}.topbar-actions .btn{flex:1}.form-grid{grid-template-columns:1fr}.form-grid .full{grid-column:span 1}}
</style>
</head>
<body>
<div class="page-shell">
<div class="app">
  <aside class="sidebar">
    <div class="brand">
      <div class="logo">VT</div>
      <div><h1>VoteTrack Pro</h1><p>Biometric election hub</p></div>
    </div>
    <div class="nav-label">Menu</div>
    <nav class="sidebar-nav">
      <button class="active" onclick="showPage('dashboard',this)">📊 Dashboard</button>
      <button onclick="showPage('register',this)">➕ Enroll Voter</button>
      <button onclick="showPage('history',this)">📈 Live Results</button>
      <button onclick="showPage('records',this)">👥 Voter Management</button>
    </nav>
    <div class="device-box">
      <b>ESP32 Dashboard</b><br>
      WiFi: <span id="wifiText">Checking...</span> <span id="wifiDot" class="dot"></span><br>
      IP: <span id="ipText">--</span><br>
      Last update: <span id="apiTime">--</span>
    </div>
  </aside>
 
  <main class="main dash-view">
    <header class="topbar">
      <div>
        <span class="live-pill"><span class="live-dot"></span> Live</span>
        <h2 id="pageTitle">Voting Dashboard</h2>
        <p id="pageSubtitle">Live fingerprint voting, candidate results, and voter records.</p>
      </div>
      <div class="topbar-actions">
        <button class="btn btn-light" id="soundToggleBtn" onclick="toggleSound()">🔇 Enable Sound</button>
        <button class="btn btn-success" onclick="exportVotesCsv()">Export Votes CSV</button>
        <button class="btn btn-danger" onclick="resetElection()">Reset Election</button>
      </div>
    </header>
  <section id="page-dashboard" class="page dash-page active">
    <div id="winnerAnnouncement" class="winner-banner empty"><span class="banner-icon">📊</span><span>No votes cast yet. Waiting for the first vote...</span></div>
 
    <div class="row dash-stats">
      <div class="col-3"><div class="card stat-card stat-accent-1"><div class="stat-icon">👥</div><div class="label">Total Voters</div><div class="value" id="dashTotalVoters">--</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-2"><div class="stat-icon">🗳️</div><div class="label">Votes Cast</div><div class="value" id="dashVotesCast">0</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-3"><div class="stat-icon">📈</div><div class="label">Turnout</div><div class="value" id="dashTurnout">0%</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-4"><div class="stat-icon">🏆</div><div class="label">Leading</div><div class="value" id="dashLeading" style="font-size:1.05rem">--</div></div></div>
    </div>
 
    <div class="dash-split">
      <div class="card panel-card dash-votes">
        <div class="card-header"><span class="card-header-title">Vote Distribution</span><span class="card-header-meta" id="lastUpdated">--</span></div>
        <div class="card-body" id="voteDistributionPanel">Loading results...</div>
      </div>
      <div class="card panel-card dash-feed">
        <div class="card-header"><span class="card-header-title">Live Activity</span><button class="btn btn-light btn-sm" style="background:rgba(255,255,255,.2);color:#fff;border:0" onclick="refreshNow(true)">Refresh</button></div>
        <div class="card-body">
          <div class="table-wrap"><table><thead><tr><th>Time</th><th>Event</th><th>Voter</th><th>Candidate</th></tr></thead><tbody id="liveBody"></tbody></table></div>
          <div id="debugStrip" class="dash-feed-footer">Waiting for dashboard data...</div>
        </div>
      </div>
    </div>
  </section>
 
  <section id="page-register" class="page reg-page">
    <div class="row reg-stats">
      <div class="col-3"><div class="card stat-card stat-accent-1"><div class="stat-icon">👥</div><div class="label">Total Enrolled</div><div class="value" id="totalEnrolled">--</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-2"><div class="stat-icon">🗳️</div><div class="label">Votes Cast</div><div class="value" id="totalVotes">0</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-3"><div class="stat-icon">🏆</div><div class="label">Leading</div><div class="value" id="leadingCandidate" style="font-size:1.05rem">--</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-4"><div class="stat-icon">🔢</div><div class="label">Next ID</div><div class="value" id="nextId">--</div></div></div>
    </div>
    <div class="card reg-card">
      <div class="card-header"><span class="card-header-title">Voter Enrollment</span><span class="card-header-meta">Dashboard registration</span></div>
      <div class="card-body">
        <div class="reg-layout">
          <div class="reg-side">
            <div class="fingerprint-scan"></div>
            <strong id="registerStatusText">Ready</strong>
            <p class="reg-hint">Fill in voter details, then start registration and scan on the R503 sensor.</p>
            <div class="register-steps">
              <div class="reg-step active" id="regStepInfo">1. Voter Details</div>
              <div class="reg-step" id="regStepScan">2. Finger Scan</div>
              <div class="reg-step" id="regStepSave">3. Save Record</div>
            </div>
          </div>
          <div class="reg-form-wrap">
            <div class="form-grid">
              <div class="form-group"><label>Name</label><input id="enrollName" placeholder="Full name" autocomplete="name"></div>
              <div class="form-group"><label>ID No</label><input id="enrollIdNo" placeholder="Voter ID number"></div>
              <div class="form-group"><label>Date of Birth</label><input type="date" id="enrollDob"></div>
              <div class="form-group"><label>Sex</label><select id="enrollSex"><option value="">Select sex</option><option value="Male">Male</option><option value="Female">Female</option></select></div>
              <div class="form-group full"><label>City</label><input id="enrollCity" placeholder="City"></div>
            </div>
            <div id="registerWarning" class="register-warning">Please fill in Name, ID No, Date of Birth, Sex, and City before starting registration.</div>
            <div class="toolbar reg-toolbar">
              <button class="btn btn-success" onclick="startEnroll()">Start Registration</button>
              <button class="btn btn-light" onclick="clearRegisterForm()">Clear Form</button>
              <button class="btn btn-danger" onclick="cancelEnroll()">Cancel Enrollment</button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </section>
 
  <section id="page-history" class="page res-page">
    <div id="resWinnerAnnouncement" class="winner-banner empty"><span class="banner-icon">📊</span><span>No votes cast yet. Waiting for the first vote...</span></div>
 
    <div class="row dash-stats">
      <div class="col-3"><div class="card stat-card stat-accent-1"><div class="stat-icon">👥</div><div class="label">Total Voters</div><div class="value" id="resTotalVoters">--</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-2"><div class="stat-icon">🗳️</div><div class="label">Votes Cast</div><div class="value" id="resVotesCast">0</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-3"><div class="stat-icon">📈</div><div class="label">Turnout</div><div class="value" id="resTurnout">0%</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-4"><div class="stat-icon">🏆</div><div class="label">Leading</div><div class="value" id="resLeading" style="font-size:1.05rem">--</div></div></div>
    </div>
 
    <div class="card panel-card res-results-card">
      <div class="card-header"><span class="card-header-title">Live Results</span><span class="card-header-meta" id="resLastUpdated">Updated --</span></div>
      <div class="card-body" id="liveResultsPanel">Loading results...</div>
    </div>
 
    <div class="card panel-card res-history-card">
      <div class="card-header"><span class="card-header-title">Vote History</span><span class="card-header-meta">Recorded votes only</span></div>
      <div class="card-body">
        <div class="table-wrap"><table><thead><tr><th>Time</th><th>Voter</th><th>ID No</th><th>Finger ID</th><th>Candidate</th><th>Message</th></tr></thead><tbody id="historyBody"></tbody></table></div>
      </div>
    </div>
  </section>
 
  <section id="page-records" class="page records-page">
    <div class="row dash-stats">
      <div class="col-3"><div class="card stat-card stat-accent-1"><div class="stat-icon">👥</div><div class="label">Registered</div><div class="value" id="recRegistered">--</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-2"><div class="stat-icon">🗳️</div><div class="label">Voted</div><div class="value" id="recVoted">0</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-3"><div class="stat-icon">⏳</div><div class="label">Not Voted</div><div class="value" id="recPending">0</div></div></div>
      <div class="col-3"><div class="card stat-card stat-accent-4"><div class="stat-icon">🔢</div><div class="label">Next ID</div><div class="value" id="recNextId">--</div></div></div>
    </div>
 
    <div class="card panel-card records-card">
      <div class="card-header"><span class="card-header-title">Registered Voters</span><span class="card-header-meta"><span id="recLastUpdated">Updated --</span> · <span id="registeredCount">--</span> on file</span></div>
      <div class="card-body">
        <div class="table-wrap"><table><thead><tr><th>Finger ID</th><th>Name</th><th>ID No</th><th>DOB</th><th>Sex</th><th>City</th><th>Status</th><th>Actions</th></tr></thead><tbody id="recordsBody"></tbody></table></div>
      </div>
    </div>
  </section>
  </main>
</div>
</div>
 
<div id="banner" class="banner"><strong id="bannerTitle">Message</strong><div id="bannerText" style="font-size:.88rem;color:var(--muted);margin-top:4px">Details</div></div>
<div id="liveModal" class="live-modal"><div id="liveCard" class="live-card modal-info"><div id="modalIcon" class="modal-icon info">ℹ</div><h2 id="modalTitle">Notice</h2><p id="modalMessage">Action completed.</p><div class="detail-grid"><div class="detail" id="modalFieldName"><span>Name</span><strong id="modalName">-</strong></div><div class="detail" id="modalFieldId"><span>Finger ID</span><strong id="modalId">-</strong></div><div class="detail" id="modalFieldIdNo"><span>ID No</span><strong id="modalIdNo">-</strong></div><div class="detail" id="modalFieldDob"><span>Date of Birth</span><strong id="modalDob">-</strong></div><div class="detail" id="modalFieldSex"><span>Sex</span><strong id="modalSex">-</strong></div><div class="detail" id="modalFieldCity"><span>City</span><strong id="modalCity">-</strong></div><div class="detail" id="modalFieldCandidate"><span>Candidate</span><strong id="modalCandidate">-</strong></div><div class="detail" id="modalFieldEvent"><span>Status</span><strong id="modalEvent">-</strong></div></div><div style="margin-top:18px"><button class="btn btn-primary" onclick="closeModal()">Done</button></div></div></div>
 
<script>
let state={},logs=[],registeredFingerprints=[],lastSeenKey="",firstLoad=true,soundEnabled=false,modalTimer=null;
const CAND_COLORS=["bar-0","bar-1","bar-2","bar-3"];
function showPage(name,btn){
  document.querySelectorAll(".page").forEach(p=>p.classList.remove("active"));
  document.getElementById("page-"+name).classList.add("active");
  document.querySelectorAll(".sidebar-nav button").forEach(b=>b.classList.remove("active"));
  if(btn)btn.classList.add("active");
  const mainEl=document.querySelector(".main");
  if(mainEl)mainEl.classList.toggle("dash-view",name==="dashboard");
  if(name==="dashboard"){pageTitle.textContent="Voting Dashboard";pageSubtitle.textContent="Live fingerprint voting, candidate results, and voter records."}
  else if(name==="register"){pageTitle.textContent="Enroll Voter";pageSubtitle.textContent="Register voters with fingerprint scan on the R503 sensor."}
  else if(name==="history"){pageTitle.textContent="Live Results";pageSubtitle.textContent="Real-time vote distribution and election analytics."}
  else{pageTitle.textContent="Voter Management";pageSubtitle.textContent="View, refresh, and delete enrolled voters."}
}
async function api(path,options={}){const res=await fetch(path,options);if(!res.ok){const txt=await res.text();throw new Error(txt||("HTTP "+res.status))}return res.json()}
function toggleSound(){soundEnabled=!soundEnabled;const btn=document.getElementById("soundToggleBtn");if(soundEnabled){if(btn)btn.textContent="🔊 Disable Sound";beep("info")}else{if(btn)btn.textContent="🔇 Enable Sound"}}
function beep(type="info"){if(!soundEnabled)return;try{const C=window.AudioContext||window.webkitAudioContext;const ctx=new C();const osc=ctx.createOscillator();const gain=ctx.createGain();osc.connect(gain);gain.connect(ctx.destination);osc.frequency.value=type==="success"?880:type==="error"?180:520;gain.gain.setValueAtTime(.0001,ctx.currentTime);gain.gain.exponentialRampToValueAtTime(.15,ctx.currentTime+.02);gain.gain.exponentialRampToValueAtTime(.0001,ctx.currentTime+.18);osc.start();osc.stop(ctx.currentTime+.2)}catch(e){}}
function showBanner(type,title,text){bannerTitle.textContent=title;bannerText.textContent=text||"";banner.className="banner show "+(type==="success"?"success":type==="error"?"error":type==="info"?"info":"");setTimeout(()=>banner.className="banner",4500)}
function modalIconChar(type){if(type==="success")return"✓";if(type==="error")return"✕";if(type==="warning")return"!";return"ℹ"}
function normalizeModalData(data={}){return{name:data.name||"",id:data.id,collegeId:data.collegeId||data.idNo||"",note:data.note||data.dob||"",role:data.role||data.sex||"",department:data.department||data.city||"",candidate:data.candidate||"",event:data.event||""}}
function getEnrollFormData(){return{name:(enrollName?.value||"").trim(),collegeId:(enrollIdNo?.value||"").trim(),note:(enrollDob?.value||""),role:(enrollSex?.value||""),department:(enrollCity?.value||"").trim(),id:-1}}
function setModalFields(fields,data){const map={name:["modalFieldName","modalName"],id:["modalFieldId","modalId",v=>v>=0?String(v):"-"],idNo:["modalFieldIdNo","modalIdNo"],dob:["modalFieldDob","modalDob"],sex:["modalFieldSex","modalSex"],city:["modalFieldCity","modalCity"],candidate:["modalFieldCandidate","modalCandidate"],event:["modalFieldEvent","modalEvent"]};Object.keys(map).forEach(key=>{const[fieldId,valueId,fmt]=map[key];const wrap=document.getElementById(fieldId);const el=document.getElementById(valueId);const show=fields.includes(key);let val="";if(key==="name")val=data.name||"-";else if(key==="id")val=fmt?fmt(data.id):data.id;else if(key==="idNo")val=data.collegeId||"-";else if(key==="dob")val=data.note||"-";else if(key==="sex")val=data.role||"-";else if(key==="city")val=data.department||"-";else if(key==="candidate")val=data.candidate||"-";else if(key==="event")val=data.event||"-";if(wrap){wrap.classList.toggle("hidden",!show);if(show&&el)el.textContent=val||"-"}})}
function showModal(type,title,message,data={},options={}){const d=normalizeModalData(data);const fields=options.fields||["name","id","idNo","dob","sex","city"];liveCard.className="live-card modal-"+(type||"info");modalIcon.className="modal-icon "+(type||"info");modalIcon.textContent=modalIconChar(type||"info");modalTitle.textContent=title||"Notice";modalMessage.textContent=message||"";setModalFields(fields,d);liveModal.classList.add("show");if(modalTimer)clearTimeout(modalTimer);modalTimer=setTimeout(()=>closeModal(),options.autoCloseMs||8000)}
function closeModal(){liveModal.classList.remove("show");if(modalTimer){clearTimeout(modalTimer);modalTimer=null}}
function eventType(event){event=(event||"").toUpperCase();if(event==="VOTE")return"vote";if(event.includes("ALREADY VOTED"))return"already";if(event.includes("VOTE PENDING"))return"vote-pending";if(event.includes("VOTE TIMEOUT"))return"vote-timeout";if(event.includes("DUPLICATE"))return"duplicate";if(event.includes("NOT FOUND"))return"not-found";if(event.includes("ENROLLED"))return"enrolled";if(event.includes("ENROLL REQUEST"))return"enroll-request";if(event.includes("ENROLL"))return"enroll";if(event.includes("RESET"))return"reset";if(event.includes("CANCEL"))return"cancel";if(event.includes("ERROR"))return"error";return"info"}
function eventBadge(event){const t=eventType(event);if(t==="vote")return"b-vote";if(t==="already")return"b-already";if(t==="vote-pending")return"b-vote-pending";if(t==="duplicate")return"b-already";if(t==="vote-timeout")return"b-error";if(t==="enrolled")return"b-enrolled";if(t==="error"||t==="not-found")return"b-error";return"b-info"}
function eventKey(l){if(!l)return"";return[l.time,l.event,l.id,l.message,l.candidate].join("|")}
function personName(l){return l.name||(l.id>=0?("ID "+l.id):"System")}
function escapeHtml(v){return String(v??"").replace(/[&<>"']/g,ch=>({"&":"&amp;","<":"&lt;",">":"&gt;","\"":"&quot;","'":"&#39;"}[ch]))}
function getVoterTurnout(){const voters=Number(state.templates||0);const votes=Number(state.totalVotes||0);return voters>0?Math.round((votes/voters)*100):0}
function getLeadingInfo(){const counts=state.voteCounts||[0,0,0,0];const names=state.candidates||["Candidate 1","Candidate 2","Candidate 3","Candidate 4"];let max=-1,leader="--",leadVotes=0;counts.forEach((c,i)=>{const n=Number(c||0);if(n>max){max=n;leader=names[i]||("Candidate "+(i+1));leadVotes=n}});return{leader:max>0?leader:"--",leadVotes,max}}
function handleNewEvent(l){if(!l)return;const ev=(l.event||"").toUpperCase();const type=eventType(l.event);const name=personName(l);const msg=l.message||"";const cand=l.candidate||"";const data=normalizeModalData(l);if(type==="enrolled"){setRegisterStep(3);if(registerStatusText)registerStatusText.textContent="Saved successfully";showBanner("success","Registration Successful",name+" has been enrolled.");showModal("success","Registration Successful","Fingerprint saved and voter record created.",{...data,event:"Registered Successfully"},{fields:["name","id","idNo","dob","sex","city","event"],autoCloseMs:9000});beep("success")}else if(type==="vote"){showBanner("success","Voting Successful",name+" voted for "+(cand||"selected candidate")+".");showModal("success","Voting Successful","The vote was recorded successfully.",{...data,candidate:cand||data.candidate,event:"Vote Recorded"},{fields:["name","id","idNo","candidate","city"],autoCloseMs:9000});beep("success")}else if(type==="already"){showBanner("error","Already Voted",name+" has already voted in this election.");showModal("error","Already Voted","This voter cannot cast another vote.",{...data,event:"Already Voted"},{fields:["name","id","idNo","sex","city"],autoCloseMs:9000});beep("error")}else if(type==="vote-pending"){showBanner("info","Select Candidate",name+" verified — press a candidate button now.");showModal("info","Select Candidate Button","Press D5, D18, D19, or D23 within 15 seconds.",{...data,event:"Awaiting Button"},{fields:["name","id","idNo","city"],autoCloseMs:7000});beep("info")}else if(type==="vote-timeout"){showBanner("error","Vote Timed Out",name+" did not select a candidate in time.");showModal("error","Selection Timed Out","No candidate button was pressed in time. Scan again to vote.",{...data,event:"Timed Out"},{fields:["name","id","idNo"],autoCloseMs:9000});beep("error")}else if(type==="duplicate"){setRegisterStep(1);if(registerStatusText)registerStatusText.textContent="Duplicate detected";showBanner("error","Duplicate Registration","This fingerprint is already enrolled on the sensor.");showModal("error","Duplicate Registration","Scan a different finger or delete the existing record first.",{...data,event:"Duplicate Fingerprint"},{fields:["id","name","idNo","sex","city"],autoCloseMs:9000});beep("error")}else if(type==="not-found"){showBanner("error","Fingerprint Not Found",msg||"No matching voter was found.");showModal("error","Fingerprint Not Found",msg||"This fingerprint is not registered in the system.",{event:"Not Found",message:msg},{fields:["event"],autoCloseMs:8000});beep("error")}else if(type==="error"){const scanAgain=msg.toLowerCase().includes("not clear")||msg.toLowerCase().includes("could not read");if(registerStatusText)registerStatusText.textContent=scanAgain?"Scan again":"Needs attention";if(scanAgain)setRegisterStep(2);showBanner("error",scanAgain?"Scan Again":"Action Failed",msg||"Please try again.");showModal("error",scanAgain?"Scan Again":"Action Failed",scanAgain?"Place the same finger flat on the sensor and hold still.":(msg||"Please try again."),{...data,event:l.event||"Error"},{fields:scanAgain?["event"]:["name","idNo","event"],autoCloseMs:9000});beep("error")}else if(type==="enroll"){setRegisterStep(2);if(registerStatusText)registerStatusText.textContent="Scanning finger";const form=getEnrollFormData();showBanner("info","Scan Fingerprint","Place finger on the R503 sensor.");showModal("info","Scan Fingerprint","Complete fingerprint capture on the sensor.",{...form,...data,event:"Scan Required"},{fields:["name","idNo","dob","sex","city","event"],autoCloseMs:8000});beep("info")}else if(type==="enroll-request"){showBanner("info","Enrollment Queued","Waiting for fingerprint scan on the sensor.");beep("info")}else if(type==="reset"){showBanner("info","Election Reset","All votes have been cleared.");showModal("info","Election Reset","Vote counts reset. Every voter may vote again.",{event:"Election Reset"},{fields:["event"],autoCloseMs:7000});beep("info")}else if(type==="cancel"){setRegisterStep(1);if(registerStatusText)registerStatusText.textContent="Cancelled";showBanner("info","Enrollment Cancelled","Registration was cancelled.");showModal("warning","Enrollment Cancelled","You can fill the form and start again when ready.",{event:"Cancelled"},{fields:["event"],autoCloseMs:6000});beep("info")}}
function updateRecordsStats(){const people=buildPeopleRecords();const voted=people.filter(p=>p.status==="Voted").length;const registered=people.length;const pending=Math.max(registered-voted,0);if(recRegistered)recRegistered.textContent=registered;if(recVoted)recVoted.textContent=voted;if(recPending)recPending.textContent=pending;if(recNextId)recNextId.textContent=state.nextId??"--";if(registeredCount)registeredCount.textContent=registered}
function statusBadgeClass(status){if(status==="Voted")return"b-vote";if(status==="Registered")return"b-enrolled";return"b-info"}
function buildPeopleRecords(){const people={};registeredFingerprints.forEach(fp=>{const id=Number(fp.id);if(id<0)return;people[id]={id:id,name:fp.name||"",collegeId:fp.collegeId||"",role:fp.role||"",department:fp.department||"",dob:fp.dob||"",status:fp.name||fp.collegeId?"Registered":"Unassigned"}});logs.forEach(l=>{const id=Number(l.id);if(id<0||!people[id])return;if(l.name)people[id].name=l.name;if(l.collegeId)people[id].collegeId=l.collegeId;if(l.role)people[id].role=l.role;if(l.department)people[id].department=l.department;const ev=(l.event||"").toUpperCase();if(ev.includes("ENROLLED"))people[id].status="Registered";if(ev==="VOTE")people[id].status="Voted"});return Object.values(people).sort((a,b)=>a.id-b.id)}
function buildVoteLog(){return logs.filter(l=>(l.event||"").toUpperCase()==="VOTE").slice().reverse().map(l=>({time:l.time||"",name:l.name||("ID "+l.id),collegeId:l.collegeId||"-",id:l.id,candidate:l.candidate||"-",message:l.message||""}))}
function renderCandidatePanels(containerId,tableId){const el=document.getElementById(containerId);if(!el)return;const counts=state.voteCounts||[0,0,0,0];const names=state.candidates||["Candidate 1","Candidate 2","Candidate 3","Candidate 4"];const total=counts.reduce((a,b)=>a+Number(b||0),0);const lead=getLeadingInfo().leader;let html="";names.forEach((name,i)=>{const votes=Number(counts[i]||0);const pct=total>0?((votes/total)*100).toFixed(1):"0.0";const isLead=name===lead&&total>0;const barWidth=votes>0?Math.max(parseFloat(pct),8):0;html+=`<div class="candidate-row cand-${i%4} ${isLead?"leading":""}"><div class="candidate-main"><span class="cand-badge">${i+1}</span><div class="candidate-info"><span class="candidate-name">${escapeHtml(name)}</span><span class="candidate-meta">${votes} vote${votes===1?"":"s"} · ${pct}%</span></div>${isLead?'<span class="cand-lead-tag">Leading</span>':""}</div><div class="progress"><div class="progress-bar bar-${i%4} ${votes?"":"empty"}" style="width:${barWidth}%"></div></div></div>`});el.innerHTML=html||"<div style='color:var(--muted);text-align:center;padding:20px'>No votes yet.</div>";const tb=document.getElementById(tableId);if(tb){tb.innerHTML=names.map((name,i)=>{const votes=Number(counts[i]||0);const pct=total>0?((votes/total)*100).toFixed(1):"0.0";const isLead=name===lead&&total>0;const barWidth=votes>0?Math.max(parseFloat(pct),10):0;return `<tr class="${isLead?"leading-row":""}"><td>${escapeHtml(name)}</td><td>${votes}</td><td>${pct}%</td><td><div class="progress"><div class="progress-bar bar-${i%4} ${votes?"":"empty"}" style="width:${barWidth}%"></div></div></td><td>${isLead?"Leading":"-"}</td></tr>`}).join("")}}
function renderWinnerBanner(){const info=getLeadingInfo();const total=Number(state.totalVotes||0);const turnout=getVoterTurnout();const emptyHtml='<span class="banner-icon">📊</span><span>No votes cast yet. Waiting for the first vote...</span>';const leadHtml=`<span class="banner-icon">🏆</span><span><strong>${escapeHtml(info.leader)}</strong> is leading with ${info.leadVotes} votes (${total>0?Math.round((info.leadVotes/total)*100):0}% of total) · Turnout: ${turnout}%</span>`;["winnerAnnouncement","resWinnerAnnouncement"].forEach(id=>{const el=document.getElementById(id);if(!el)return;if(total===0){el.className="winner-banner empty";el.innerHTML=emptyHtml}else{el.className="winner-banner";el.innerHTML=leadHtml}})}
function renderLiveTicker(){const el=document.getElementById("liveTicker");if(!el)return;const items=logs.slice().reverse().slice(0,12);if(!items.length){el.innerHTML="<div class='vote-activity-item'>No activity yet.</div>";return}el.innerHTML=items.map(l=>`<div class="vote-activity-item"><strong>${escapeHtml(l.time||"")}</strong> — <span class="badge ${eventBadge(l.event)}">${escapeHtml(l.event||"INFO")}</span> ${escapeHtml(personName(l))}${l.candidate?" → "+escapeHtml(l.candidate):""}</div>`).join("")}
function renderSystemStatus(){const wifi=!!state.wifi;const wifiEl=document.getElementById("wifiStatus");const sensorEl=document.getElementById("sensorStatus");const deviceEl=document.getElementById("deviceStatus");const wifiTextEl=document.getElementById("wifiText");const wifiDotEl=document.getElementById("wifiDot");if(wifiTextEl)wifiTextEl.textContent=wifi?"Connected":"Offline";if(wifiDotEl)wifiDotEl.className="dot "+(wifi?"ok":"");if(wifiEl){wifiEl.textContent=wifi?"Connected":"Offline";wifiEl.className="status-badge "+(wifi?"ok":"bad")}if(sensorEl){sensorEl.textContent=state.sensor||"Ready";sensorEl.className="status-badge ok"}if(deviceEl){deviceEl.textContent=wifi?"Online":"Offline";deviceEl.className="status-badge "+(wifi?"ok":"bad")}}
function renderTables(){const onDash=document.getElementById("page-dashboard")?.classList.contains("active");const liveRows=logs.slice().reverse().map(l=>onDash?`<tr><td>${escapeHtml(l.time||"")}</td><td><span class="badge ${eventBadge(l.event)}">${escapeHtml(l.event||"INFO")}</span></td><td>${escapeHtml(l.name||"-")}</td><td>${escapeHtml(l.candidate||"-")}</td></tr>`:`<tr><td>${escapeHtml(l.time||"")}</td><td><span class="badge ${eventBadge(l.event)}">${escapeHtml(l.event||"INFO")}</span></td><td>${l.id>=0?l.id:"-"}</td><td>${escapeHtml(l.name||"-")}</td><td>${escapeHtml(l.candidate||"-")}</td><td>${escapeHtml(l.message||"")}</td></tr>`).join("");if(liveBody)liveBody.innerHTML=liveRows||`<tr><td colspan="${onDash?4:6}">No logs yet.</td></tr>`;const historyRows=buildVoteLog().map(r=>`<tr><td>${escapeHtml(r.time)}</td><td>${escapeHtml(r.name)}</td><td>${escapeHtml(r.collegeId)}</td><td>${r.id}</td><td>${escapeHtml(r.candidate)}</td><td>${escapeHtml(r.message)}</td></tr>`).join("");if(historyBody)historyBody.innerHTML=historyRows||`<tr><td colspan="6">No votes recorded yet.</td></tr>`;const peopleRows=buildPeopleRecords().map(p=>`<tr><td>${p.id}</td><td>${escapeHtml(p.name||"-")}</td><td>${escapeHtml(p.collegeId||"-")}</td><td>${escapeHtml(p.dob||"-")}</td><td>${escapeHtml(p.role||"-")}</td><td>${escapeHtml(p.department||"-")}</td><td><span class="badge ${statusBadgeClass(p.status)}">${escapeHtml(p.status)}</span></td><td><button class="btn btn-danger btn-sm" onclick="deleteFingerprint(${p.id})">Delete</button></td></tr>`).join("");if(recordsBody)recordsBody.innerHTML=peopleRows||`<tr><td colspan="8">No registered voters yet.</td></tr>`;updateRecordsStats();renderCandidatePanels("voteDistributionPanel");renderCandidatePanels("liveResultsPanel");renderWinnerBanner();renderLiveTicker();renderSystemStatus();const lu=document.getElementById("lastUpdated");if(lu)lu.textContent="Updated "+new Date().toLocaleTimeString();const ru=document.getElementById("resLastUpdated");if(ru)ru.textContent="Updated "+new Date().toLocaleTimeString();const rc=document.getElementById("recLastUpdated");if(rc)rc.textContent="Updated "+new Date().toLocaleTimeString()}
function csvEscape(v){v=String(v??"");return '"'+v.replace(/"/g,'""')+'"'}
function exportVotesCsv(){const rows=buildVoteLog();if(!rows.length){showBanner("error","No Vote Data","No votes to export yet.");return}let csv="time,voter,college_id,fingerprint_id,candidate,message
";rows.slice().reverse().forEach(r=>{csv+=[csvEscape(r.time),csvEscape(r.name),csvEscape(r.collegeId),csvEscape(r.id),csvEscape(r.candidate),csvEscape(r.message)].join(",")+"
"});const blob=new Blob([csv],{type:"text/csv;charset=utf-8;"});const url=URL.createObjectURL(blob);const a=document.createElement("a");a.href=url;a.download="election_results_"+new Date().toISOString().split("T")[0]+".csv";document.body.appendChild(a);a.click();document.body.removeChild(a);URL.revokeObjectURL(url);showBanner("success","Export Complete","Election results exported.")}
async function resetElection(){if(!confirm("Reset the entire election? This clears all vote counts and allows every voter to vote again."))return;try{await api("/api/reset-votes",{method:"POST"});showBanner("success","Election Reset","All votes cleared.");beep("success");refreshNow()}catch(e){showBanner("error","Reset Failed",e.message);beep("error")}}
function updateStatusUi(){const wifi=!!state.wifi;const voters=state.templates??"--";const votes=state.totalVotes??0;const turnout=getVoterTurnout()+"%";const leader=getLeadingInfo().leader;if(ipText)ipText.textContent=state.ip||"--";if(apiTime)apiTime.textContent=new Date().toLocaleTimeString();if(wifiText)wifiText.textContent=wifi?"Connected":"Offline";if(wifiDot)wifiDot.className="dot "+(wifi?"ok":"");["dashTotalVoters","resTotalVoters","totalEnrolled"].forEach(id=>{const el=document.getElementById(id);if(el)el.textContent=voters});["dashVotesCast","resVotesCast","totalVotes"].forEach(id=>{const el=document.getElementById(id);if(el)el.textContent=votes});["dashTurnout","resTurnout"].forEach(id=>{const el=document.getElementById(id);if(el)el.textContent=turnout});["dashLeading","resLeading","leadingCandidate"].forEach(id=>{const el=document.getElementById(id);if(el)el.textContent=leader});if(nextId)nextId.textContent=state.nextId??"--";if(debugStrip)debugStrip.innerHTML="Logs: <b>"+logs.length+"</b> | Votes: <b>"+votes+"</b> | Turnout: <b>"+turnout+"</b> | Enrolling: <b>"+(state.isEnrolling?"YES":"NO")+"</b> | Selecting: <b>"+(state.isSelectingVote?"YES":"NO")+"</b>";if(state.isEnrolling){setRegisterStep(2);if(registerStatusText)registerStatusText.textContent="Scanning finger"}}
function setRegisterStep(step){const info=document.getElementById("regStepInfo");const scan=document.getElementById("regStepScan");const save=document.getElementById("regStepSave");if(!info||!scan||!save)return;[info,scan,save].forEach(el=>{el.classList.remove("active","done")});if(step===1)info.classList.add("active");else if(step===2){info.classList.add("done");scan.classList.add("active")}else if(step===3){info.classList.add("done");scan.classList.add("done");save.classList.add("active")}}
function clearRegisterForm(){if(enrollName)enrollName.value="";if(enrollIdNo)enrollIdNo.value="";if(enrollDob)enrollDob.value="";if(enrollSex)enrollSex.value="";if(enrollCity)enrollCity.value="";const warn=document.getElementById("registerWarning");if(warn)warn.classList.remove("show");setRegisterStep(1);if(registerStatusText)registerStatusText.textContent="Ready"}
function validateRegisterForm(){const name=(enrollName?.value||"").trim();const idNo=(enrollIdNo?.value||"").trim();const dob=(enrollDob?.value||"").trim();const sex=(enrollSex?.value||"").trim();const city=(enrollCity?.value||"").trim();const warn=document.getElementById("registerWarning");if(!name||!idNo||!dob||!sex||!city){if(warn)warn.classList.add("show");showBanner("error","Missing Details","Enter Name, ID No, Date of Birth, Sex, and City.");return false}if(warn)warn.classList.remove("show");return true}
async function refreshNow(forcePopup=false){try{const newState=await api("/api/status");const logData=await api("/api/logs");let regData={fingerprints:[]};try{regData=await api("/api/registered")}catch(e){regData={fingerprints:[]}}state=newState||{};logs=logData.logs||[];registeredFingerprints=regData.fingerprints||[];updateStatusUi();renderTables();const latest=state.last||logs[logs.length-1]||null;const key=eventKey(latest);if(firstLoad){firstLoad=false;lastSeenKey=key;if(latest&&forcePopup)handleNewEvent(latest);return}if((forcePopup&&latest)||(key&&key!==lastSeenKey)){lastSeenKey=key;handleNewEvent(latest)}}catch(e){if(debugStrip)debugStrip.innerHTML="Dashboard API error: <b>"+e.message+"</b>";showBanner("error","API Error",e.message)}}
async function startEnroll(){if(!validateRegisterForm())return;const form=getEnrollFormData();const payload=new URLSearchParams();payload.append("name",form.name);payload.append("collegeId",form.collegeId);payload.append("role",form.role);payload.append("department",form.department);payload.append("note",form.note);try{setRegisterStep(2);if(registerStatusText)registerStatusText.textContent="Scanning finger";showBanner("info","Enrollment Started","Place finger on the R503 sensor.");beep("info");await api("/api/enroll",{method:"POST",headers:{"Content-Type":"application/x-www-form-urlencoded"},body:payload});setTimeout(()=>refreshNow(),500)}catch(e){setRegisterStep(1);if(registerStatusText)registerStatusText.textContent="Failed";showBanner("error","Enrollment Failed",e.message);showModal("error","Enrollment Failed",e.message,{...form,event:"Failed"},{fields:["name","idNo","event"],autoCloseMs:9000});beep("error")}}
async function cancelEnroll(){try{await api("/api/cancel",{method:"POST"});showBanner("info","Cancelled","Enrollment cancelled.");refreshNow()}catch(e){showBanner("error","Cancel Failed",e.message)}}
async function deleteFingerprint(id){if(!id)return;if(!confirm("Delete fingerprint ID "+id+" and remove this voter record?"))return;try{await api("/api/fingerprint?id="+encodeURIComponent(id),{method:"DELETE"});showBanner("success","Deleted","Voter ID "+id+" removed.");beep("success");refreshNow()}catch(e){showBanner("error","Delete Failed",e.message);beep("error")}}
setRegisterStep(1);refreshNow();setInterval(refreshNow,1000);
</script>
</body>
</html>
)rawliteral";
 
#endif