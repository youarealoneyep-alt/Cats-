<!DOCTYPE html>
<html lang="ru">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>🐾 Котоквест: Академия кошачьих наук</title>
<style>
  :root{
    --ink:#3a2a20; --muted:#8b7668;
    --orange:#f97316; --orange-d:#ea580c;
    --purple:#7c3aed; --green:#16a34a; --red:#dc2626;
    --gold:#c9a227; --card:#fffdfa;
  }
  *{box-sizing:border-box;margin:0;padding:0}
  html,body{min-height:100%}
  body{
    font-family:'Segoe UI',system-ui,-apple-system,'Helvetica Neue',sans-serif;
    background:
      radial-gradient(circle at 10% 8%, #fff6ec 0%, transparent 42%),
      radial-gradient(circle at 92% 92%, #ffddc2 0%, transparent 48%),
      linear-gradient(135deg,#ffeede 0%,#f9c9a4 100%);
    min-height:100vh; color:var(--ink);
    display:flex; align-items:flex-start; justify-content:center;
    padding:22px 14px 48px; position:relative; overflow-x:hidden;
  }

  /* Фоновые лапки */
  .bg-paw{
    position:fixed; opacity:.13; pointer-events:none; user-select:none; z-index:0;
    animation:float 9s ease-in-out infinite;
  }
  @keyframes float{
    0%,100%{transform:translateY(0) rotate(-8deg)}
    50%{transform:translateY(-26px) rotate(8deg)}
  }

  .game{width:100%; max-width:760px; position:relative; z-index:2}

  /* ---------- Топбар ---------- */
  .topbar{display:flex; flex-direction:column; gap:9px; margin-bottom:14px}
  .progress-track{height:10px; background:#f3e5d4; border-radius:99px; overflow:hidden; box-shadow:inset 0 1px 3px rgba(0,0,0,.07)}
  .progress-bar{height:100%; width:0; border-radius:99px; background:linear-gradient(90deg,var(--orange),#fbbf24); transition:width .45s cubic-bezier(.4,0,.2,1)}
  .stats{display:flex; justify-content:space-between; gap:8px; flex-wrap:wrap}
  .stat{
    background:#fff; padding:5px 12px; border-radius:99px; border:1px solid #f0e2d0;
    font-size:13px; font-weight:800; color:var(--muted);
    font-variant-numeric:tabular-nums;
  }
  .stat.timer{transition:.25s}
  .stat.timer.danger{color:#fff; background:var(--red); border-color:var(--red); animation:pulse .8s infinite}
  @keyframes pulse{0%,100%{transform:scale(1)}50%{transform:scale(1.07)}}

  /* ---------- Карточки ---------- */
  .card{
    background:var(--card); border-radius:24px; padding:24px;
    box-shadow:0 24px 50px -26px rgba(130,80,30,.5), 0 0 0 1px #fff inset;
    animation:pop .35s cubic-bezier(.34,1.56,.64,1);
  }
  @keyframes pop{from{opacity:0;transform:scale(.96) translateY(12px)}to{opacity:1;transform:none}}

  /* ---------- Стартовый экран ---------- */
  .hero{text-align:center}
  .hero-cat{font-size:76px; line-height:1; animation:bounce 2.2s ease-in-out infinite}
  @keyframes bounce{0%,100%{transform:translateY(0) rotate(-3deg)}50%{transform:translateY(-12px) rotate(3deg)}}
  .hero h1{
    font-size:30px; line-height:1.15; margin:10px 0 12px;
    background:linear-gradient(120deg,var(--orange-d),var(--purple));
    -webkit-background-clip:text; background-clip:text; color:transparent;
  }
  .hero h1 span{font-size:16px; display:block; -webkit-text-fill-color:var(--muted); color:var(--muted); margin-top:6px; font-weight:600}
  .hero > p{font-size:15.5px; line-height:1.6; color:var(--muted); max-width:520px; margin:0 auto 20px}
  .name-box{max-width:380px; margin:0 auto; text-align:left}
  .name-box label{display:block; font-size:13px; font-weight:800; color:var(--muted); margin-bottom:6px}
  .name-box input{
    width:100%; font:inherit; font-size:17px; font-weight:600; color:var(--ink);
    padding:14px 16px; border-radius:14px; border:2px solid #eddec9; background:#fff;
    transition:.2s;
  }
  .name-box input:focus{outline:none; border-color:var(--orange); box-shadow:0 0 0 4px rgba(249,115,22,.15)}
  .error{color:var(--red); font-size:13px; font-weight:700; min-height:18px; margin:6px 0 4px}
  .shake{animation:shake .45s}
  @keyframes shake{0%,100%{transform:translateX(0)}20%{transform:translateX(-8px)}40%{transform:translateX(8px)}60%{transform:translateX(-5px)}80%{transform:translateX(5px)}}
  .hints{display:flex; justify-content:center; gap:8px; flex-wrap:wrap; margin-top:18px}
  .hints span{font-size:12.5px; font-weight:700; color:#8a6a4e; background:#fff4e6; border:1px solid #f3ddc2; padding:6px 11px; border-radius:99px}

  /* ---------- Кнопки ---------- */
  .btn{
    font:inherit; font-size:16px; font-weight:800; cursor:pointer; border:none;
    color:#fff; background:linear-gradient(135deg,var(--orange),var(--orange-d));
    padding:14px 24px; border-radius:16px;
    box-shadow:0 12px 24px -12px rgba(234,88,12,.9);
    transition:transform .15s ease, box-shadow .15s ease, opacity .2s;
    display:inline-flex; align-items:center; justify-content:center; gap:8px;
  }
  .btn:hover:not(:disabled){transform:translateY(-2px); box-shadow:0 16px 28px -12px rgba(234,88,12,.95)}
  .btn:active:not(:disabled){transform:translateY(1px) scale(.99)}
  .btn:disabled{opacity:.45; cursor:not-allowed; box-shadow:none}
  .btn.big{width:100%; margin-top:14px; font-size:17px}
  .btn.ghost{background:#fff; color:var(--orange-d); border:2px solid #f3d3b6; box-shadow:none}
  .btn.ghost:hover{background:#fff7ef; box-shadow:none}

  /* ---------- Вопрос ---------- */
  .q-meta{display:flex; justify-content:space-between; align-items:center; gap:10px; flex-wrap:wrap; margin-bottom:14px}
  .badge{
    font-size:11.5px; font-weight:800; letter-spacing:.07em; text-transform:uppercase;
    color:var(--purple); background:#f3ecff; padding:6px 12px; border-radius:99px;
  }
  .q-type{font-size:12px; font-weight:700; color:var(--muted)}
  .q-emoji{font-size:46px; line-height:1; margin-bottom:8px}
  .q-text{font-size:20px; line-height:1.45; font-weight:800; margin-bottom:18px}

  .options{display:flex; flex-direction:column; gap:10px}
  .option{
    position:relative; display:flex; align-items:center; gap:12px; width:100%;
    text-align:left; font:inherit; font-size:16px; font-weight:600; color:var(--ink);
    padding:14px 16px; border-radius:16px; border:2px solid #f0e3d2; background:#fff;
    cursor:pointer; transition:transform .15s, border-color .2s, background .2s, box-shadow .15s;
  }
  .option:hover:not(:disabled){transform:translateY(-2px); border-color:var(--orange); box-shadow:0 10px 20px -16px rgba(249,115,22,.9)}
  .option .letter{
    width:28px; height:28px; flex:0 0 28px; border-radius:9px;
    background:#f6ecdd; color:#9a7b5f; display:grid; place-items:center;
    font-size:13px; font-weight:800; transition:.2s;
  }
  .option.correct{border-color:var(--green); background:#eafaf0; color:#14532d}
  .option.correct .letter{background:var(--green); color:#fff}
  .option.wrong{border-color:var(--red); background:#fdecec; color:#7f1d1d}
  .option.wrong .letter{background:var(--red); color:#fff}
  .option:disabled{cursor:default}

  /* Мультивыбор */
  .option.check .box{
    width:22px; height:22px; flex:0 0 22px; border-radius:7px;
    border:2px solid #e2cdb2; position:relative; transition:.15s;
  }
  .option.check.selected{border-color:var(--purple); background:#f7f2ff}
  .option.check.selected .box{background:var(--purple); border-color:var(--purple)}
  .option.check.selected .box::after{
    content:"✓"; position:absolute; inset:0; display:grid; place-items:center;
    color:#fff; font-size:13px; font-weight:800;
  }

  /* Верно / неверно */
  .tf-row{display:flex; gap:12px}
  .tf-row .option{justify-content:center; font-size:17px; padding:18px 12px}
  .tf-emoji{font-size:20px; line-height:1}

  /* Соотнесение */
  .match-list{display:flex; flex-direction:column; gap:10px}
  .match-row{
    display:flex; align-items:center; gap:10px; flex-wrap:wrap;
    background:#fdf7ef; border:2px solid #f4e7d5; border-radius:14px; padding:10px 12px;
  }
  .match-left{flex:1 1 140px; font-weight:800; font-size:15px}
  .match-select{
    flex:2 1 220px; font:inherit; font-size:14px; font-weight:600; color:var(--ink);
    padding:10px 12px; border-radius:12px; border:2px solid #ecdcbf; background:#fff;
    cursor:pointer; transition:.2s;
  }
  .match-select:focus{outline:none; border-color:var(--orange)}
  .match-select.ok{border-color:var(--green); background:#eefaf1}
  .match-select.bad{border-color:var(--red); background:#fdeeee}
  .match-mark{width:24px; text-align:center; font-size:18px; font-weight:800}
  .match-mark.ok{color:var(--green)}
  .match-mark.bad{color:var(--red)}

  /* ---------- Обратная связь ---------- */
  .feedback{
    margin-top:16px; padding:16px; border-radius:16px; border-left:5px solid var(--purple);
    background:#f8f3ec; animation:fadeUp .3s ease;
  }
  .feedback.ok{background:#eefaf2; border-left-color:var(--green)}
  .feedback.bad{background:#fdf0f0; border-left-color:var(--red)}
  .fb-head{font-size:17px; font-weight:900; margin-bottom:6px}
  .feedback.ok .fb-head{color:#15803d}
  .feedback.bad .fb-head{color:#b91c1c}
  .fb-expl{font-size:14.5px; line-height:1.55; color:#5b483a}
  .fb-foot{display:flex; justify-content:space-between; align-items:center; gap:12px; margin-top:14px; flex-wrap:wrap}
  .fb-points{font-size:15px; font-weight:900; color:var(--orange-d)}
  @keyframes fadeUp{from{opacity:0;transform:translateY(8px)}to{opacity:1;transform:none}}

  /* ---------- Результат / диплом ---------- */
  .result-card{margin-bottom:16px; text-align:center}
  .result-h{font-size:23px; margin-bottom:6px; color:var(--orange-d)}
  .result-sub{font-size:14.5px; color:var(--muted); line-height:1.5}

  #diploma{
    position:relative; max-width:720px; margin:0 auto;
    background:#fffdf7; color:#3a2a20;
    border:3px solid var(--gold); border-radius:16px;
    padding:32px 28px 22px; text-align:center;
    font-family:Georgia,'Times New Roman',serif;
    box-shadow:0 30px 60px -30px rgba(120,80,20,.55), 0 0 0 8px #fffdf7, 0 0 0 10px #e8cf8a;
  }
  #diploma::before{
    content:""; position:absolute; inset:10px; border:1px solid #e3cd93;
    border-radius:10px; pointer-events:none;
  }
  .dip-corner{position:absolute; font-size:20px; opacity:.4}
  .dip-corner.tl{top:12px; left:16px}
  .dip-corner.tr{top:12px; right:16px}
  .dip-corner.bl{bottom:12px; left:16px}
  .dip-corner.br{bottom:12px; right:16px}

  .dip-academy{font-size:11.5px; letter-spacing:.28em; text-transform:uppercase; color:#8a6d1f; margin-bottom:4px}
  .dip-title{font-size:44px; letter-spacing:.16em; color:#a8741a; font-weight:700; line-height:1.1}
  .dip-sub{font-style:italic; font-size:14.5px; color:#7b6a5a; margin-top:4px}
  .dip-name{
    display:inline-block; font-family:'Segoe Script','Brush Script MT',cursive;
    font-size:36px; color:#6b3fa0; margin:14px 0 8px;
    padding:0 18px 4px; border-bottom:1px dashed #d9c69a; line-height:1.25;
  }
  .dip-text{font-size:14.5px; line-height:1.65; color:#4b3a2e}
  .dip-rank{
    display:inline-block; margin:14px auto 4px; padding:8px 22px; border-radius:99px;
    background:linear-gradient(135deg,#fff3d6,#ffe1a8); border:1px solid #e3c37a;
    font-size:17px; font-weight:700; color:#8a5a00;
  }
  .dip-stats{display:flex; justify-content:center; gap:28px; margin:16px 0 8px; flex-wrap:wrap}
  .dip-stats div span{display:block; font-family:'Segoe UI',sans-serif; font-size:25px; font-weight:800; color:#a8741a; line-height:1.1}
  .dip-stats div small{display:block; font-family:'Segoe UI',sans-serif; font-size:10px; letter-spacing:.14em; text-transform:uppercase; color:#9a8a78; margin-top:3px}
  .dip-footer{
    display:flex; justify-content:space-between; align-items:center; gap:12px;
    margin-top:18px; font-size:12.5px; color:#6d5b4b; text-align:left;
  }
  .dip-seal{font-size:32px; line-height:1; color:#a8741a; text-align:center}
  .dip-seal small{display:block; font-size:8.5px; letter-spacing:.12em; text-transform:uppercase; color:#9a8a78; margin-top:3px}
  .dip-sign{text-align:right}
  .dip-sign b{display:block; margin-top:4px; font-size:14px}
  .dip-no{margin-top:14px; font-size:11.5px; letter-spacing:.09em; color:#9a8a78}

  .actions{display:flex; gap:10px; justify-content:center; flex-wrap:wrap; margin-top:18px}
  .print-hint{text-align:center; font-size:13px; color:var(--muted); margin-top:10px}

  @media (max-width:520px){
    .card{padding:18px 15px; border-radius:20px}
    .hero h1{font-size:24px}
    .q-text{font-size:17.5px}
    .option{font-size:15px; padding:12px 13px}
    .q-emoji{font-size:38px}
    .dip-title{font-size:32px}
    .dip-name{font-size:27px}
    .dip-stats{gap:16px}
    #diploma{padding:24px 16px 18px}
  }

  /* ---------- Печать: только диплом ---------- */
  @media print{
    @page{size:A4 landscape; margin:10mm}
    body{background:#fff; padding:0; display:block}
    body *{visibility:hidden}
    #diploma, #diploma *{visibility:visible}
    #diploma{
      position:absolute; left:0; top:0; width:100%; margin:0;
      box-shadow:none; border-radius:0;
      -webkit-print-color-adjust:exact; print-color-adjust:exact;
    }
    .no-print, .no-print-head, .bg-paw{display:none !important}
  }
</style>
</head>
<body>

<div class="game">
  <div class="topbar" id="topbar" style="display:none">
    <div class="progress-track"><div class="progress-bar" id="progressBar"></div></div>
    <div class="stats">
      <span class="stat" id="qStat">1/12</span>
      <span class="stat timer" id="timerStat">⏱ 45</span>
      <span class="stat" id="scoreStat">⭐ 0</span>
    </div>
  </div>
  <main id="app"></main>
</div>

<script>
/* =========================================================
   ВОПРОСЫ
   ========================================================= */
const QUESTIONS = [
  {
    type: 'single', emoji: '🦁',
    text: 'Какая порода официально считается самой крупной домашней кошкой?',
    options: ['Британская короткошёрстная', 'Мейн-кун', 'Абиссинская', 'Канадский сфинкс'],
    correct: 1,
    expl: 'Мейн-кун — самая крупная домашняя порода: коты весят 7–12 кг, а шерстяной «воротник» делает их похожими на маленьких львов.'
  },
  {
    type: 'tf', emoji: '🏴',
    text: 'У шотландской вислоухой уши загибаются вперёд из-за мутации хрящевой ткани.',
    correct: true,
    expl: 'Да, это генетическая особенность хрящей. Именно из-за неё ушки остаются загнутыми на всю жизнь.'
  },
  {
    type: 'multi', emoji: '🛁',
    text: 'Выберите породы, у которых шерсть отсутствует или почти отсутствует:',
    options: ['Канадский сфинкс', 'Донской сфинкс', 'Петерболд', 'Корниш-рекс', 'Бенгальская', 'Мейн-кун'],
    correct: [0, 1, 2],
    expl: 'Сфинксы — канадский, донской и петерболд — породы без шерсти или с минимальным пушком. Корниш-рекс и бенгальская имеют шерсть, просто короткую.'
  },
  {
    type: 'single', emoji: '🐻',
    text: 'Какая порода известна «плюшевой» шерстью, круглой мордочкой и родом из Великобритании?',
    options: ['Британская короткошёрстная', 'Бенгальская', 'Русская голубая', 'Персидская'],
    correct: 0,
    expl: 'Британская короткошёрстная — «плюшевый медвежонок»: плотная шерсть, круглая голова и невозмутимый характер.'
  },
  {
    type: 'match', emoji: '🔗',
    text: 'Соотнесите породу и её характерную особенность:',
    left: ['Манчкин', 'Бенгальская', 'Русская голубая', 'Персидская'],
    right: ['Очень короткие лапы', 'Пятнистый «леопардовый» окрас', 'Серебристо-голубая шерсть и зелёные глаза', 'Длинная шерсть и приплюснутая мордочка'],
    correct: [0, 1, 2, 3],
    expl: 'Манчкин — короткие лапы, бенгальская — леопардовые пятна, русская голубая — серебристо-голубой окрас и зелёные глаза, персидская — длинная шерсть и плоская мордочка.'
  },
  {
    type: 'single', emoji: '🌊',
    text: 'Какая кошка знаменита любовью к воде и даже может плавать?',
    options: ['Персидская', 'Турецкий ван', 'Русская голубая', 'Шотландская вислоухая'],
    correct: 1,
    expl: 'Турецкий ван — одна из немногих пород, которые любят плавать. Шерсть у них водоотталкивающая, а купание — любимое развлечение.'
  },
  {
    type: 'tf', emoji: '📏',
    text: 'Манчкины не умеют прыгать из-за своих коротких лап.',
    correct: false,
    expl: 'Неверно: манчкины отлично прыгают и быстро бегают. Короткие лапы — особенность, а не ограничение.'
  },
  {
    type: 'multi', emoji: '🧶',
    text: 'Выберите длинношёрстные породы:',
    options: ['Персидская', 'Норвежская лесная', 'Сибирская', 'Британская короткошёрстная', 'Абиссинская'],
    correct: [0, 1, 2],
    expl: 'Персидская, норвежская лесная и сибирская — длинношёрстные. Британская короткошёрстная и абиссинская — короткошёрстные.'
  },
  {
    type: 'single', emoji: '💙',
    text: 'У какой породы ярко-зелёные глаза и серебристо-голубая шерсть с «типпингом»?',
    options: ['Британская короткошёрстная', 'Русская голубая', 'Шартрез', 'Корат'],
    correct: 1,
    expl: 'Русская голубая: двойная шерсть с серебристыми кончиками (типпинг) и яркие зелёные глаза.'
  },
  {
    type: 'single', emoji: '🐒',
    text: 'Какую породу за активность и любовь лазить называют «кошкой-обезьяной»?',
    options: ['Абиссинская', 'Мейн-кун', 'Сфинкс', 'Манчкин'],
    correct: 0,
    expl: 'Абиссинская — очень активная и любопытная, обожает высоту, поэтому её шутя называют кошкой-обезьяной.'
  },
  {
    type: 'tf', emoji: '🧴',
    text: 'Сфинксов не нужно купать: у них нет шерсти, значит кожа не пачкается.',
    correct: false,
    expl: 'Неверно: кожа сфинкса выделяет секрет, её нужно протирать и купать, а ещё защищать от солнца и сквозняков.'
  },
  {
    type: 'single', emoji: '🐆',
    text: 'Какая порода была выведена скрещиванием домашней кошки с азиатской леопардовой?',
    options: ['Бенгальская', 'Абиссинская', 'Саванна', 'Оцикет'],
    correct: 0,
    expl: 'Бенгальская — гибрид домашней кошки и азиатской леопардовой кошки. Отсюда и «леопардовый» окрас.'
  }
];

const TIME_PER_Q = 45;

/* =========================================================
   СОСТОЯНИЕ
   ========================================================= */
const state = {
  name: '',
  index: 0,
  score: 0,
  correctCount: 0,
  locked: false,
  timeLeft: TIME_PER_Q,
  timerId: null,
  matchOrder: null
};

const app = document.getElementById('app');
const topbar = document.getElementById('topbar');
const progressBar = document.getElementById('progressBar');
const esc = s => s.replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));

/* =========================================================
   ФОН
   ========================================================= */
(function createPaws(){
  const items = ['🐾','🐾','🐈','🐾','🐈‍⬛','🐾'];
  const pos = [
    {top:'6%', left:'4%'},  {top:'16%', right:'5%'},
    {top:'58%', left:'6%'}, {top:'80%', right:'8%'},
    {top:'40%', right:'3%'}, {top:'90%', left:'20%'}
  ];
  pos.forEach((p,i)=>{
    const el = document.createElement('div');
    el.className = 'bg-paw';
    el.textContent = items[i % items.length];
    Object.assign(el.style, p);
    el.style.fontSize = (28 + (i % 3) * 12) + 'px';
    el.style.animationDelay = (i * 0.8) + 's';
    document.body.appendChild(el);
  });
})();

/* =========================================================
   ТАЙМЕР
   ========================================================= */
function startTimer(){
  stopTimer();
  state.timeLeft = TIME_PER_Q;
  updateTimerUI();
  state.timerId = setInterval(()=>{
    state.timeLeft--;
    updateTimerUI();
    if(state.timeLeft <= 0){
      stopTimer();
      timeOut();
    }
  }, 1000);
}
function stopTimer(){
  if(state.timerId){ clearInterval(state.timerId); state.timerId = null; }
}
function updateTimerUI(){
  const el = document.getElementById('timerStat');
  if(!el) return;
  el.textContent = '⏱ ' + Math.max(0, state.timeLeft);
  el.classList.toggle('danger', state.timeLeft <= 10);
}

/* =========================================================
   СТАРТ
   ========================================================= */
function showStart(){
  stopTimer();
  state.name = ''; state.index = 0; state.score = 0; state.correctCount = 0; state.locked = false;
  topbar.style.display = 'none';
  app.innerHTML = `
    <div class="card hero">
      <div class="hero-cat">🐱</div>
      <h1>Котоквест<span>Академия кошачьих наук</span></h1>
      <p>12 испытаний о породах и типах кошек: один ответ, несколько ответов,
      «верно/неверно» и соотнесение. Отвечай быстро — за скорость дают бонусные очки.
      В финале тебя ждёт именной диплом!</p>
      <div class="name-box">
        <label for="nameInput">Как тебя зовут? (имя попадёт в диплом)</label>
        <input id="nameInput" type="text" maxlength="30" placeholder="Например, Алиса" autocomplete="off">
        <div class="error" id="nameError"></div>
        <button class="btn big" id="startBtn">Начать квест 🐾</button>
      </div>
      <div class="hints">
        <span>⏱ 45 секунд на вопрос</span>
        <span>⭐ бонус за скорость</span>
        <span>🎓 диплом в конце</span>
      </div>
    </div>`;

  const input = document.getElementById('nameInput');
  input.focus();
  input.addEventListener('keydown', e => { if(e.key === 'Enter') startGame(); });
  document.getElementById('startBtn').addEventListener('click', startGame);
}

function startGame(){
  const input = document.getElementById('nameInput');
  const name = input.value.trim();
  const err = document.getElementById('nameError');
  if(name.length < 2){
    err.textContent = 'Пожалуйста, введи имя (минимум 2 символа)';
    input.classList.add('shake');
    setTimeout(()=>input.classList.remove('shake'), 460);
    return;
  }
  state.name = name;
  state.index = 0;
  state.score = 0;
  state.correctCount = 0;
  state.locked = false;
  showQuestion();
}

/* =========================================================
   ЭКРАН ВОПРОСА
   ========================================================= */
function showQuestion(){
  state.locked = false;
  const q = QUESTIONS[state.index];
  const n = state.index + 1;
  const total = QUESTIONS.length;

  topbar.style.display = 'flex';
  progressBar.style.width = ((state.index) / total * 100) + '%';
  document.getElementById('qStat').textContent = n + '/' + total;
  document.getElementById('scoreStat').textContent = '⭐ ' + state.score;

  const typeLabel = {
    single: 'Выберите один ответ',
    multi: 'Выберите все верные варианты',
    tf: 'Верно или неверно?',
    match: 'Соотнесите породы и особенности'
  }[q.type];

  let inner = `
    <div class="q-meta">
      <span class="badge">Вопрос ${n} из ${total}</span>
      <span class="q-type">${typeLabel}</span>
    </div>
    <div class="q-emoji">${q.emoji}</div>
    <h2 class="q-text">${q.text}</h2>`;

  if(q.type === 'single'){
    inner += `<div class="options">` + q.options.map((o,i)=>
      `<button class="option" data-i="${i}">
         <span class="letter">${'ABCD'[i]}</span><span class="opt-label">${o}</span>
       </button>`).join('') + `</div>`;
  }

  if(q.type === 'multi'){
    inner += `<div class="options">` + q.options.map((o,i)=>
      `<button class="option check" data-i="${i}">
         <span class="box"></span><span class="opt-label">${o}</span>
       </button>`).join('') + `</div>
      <button class="btn" id="submitBtn" disabled style="margin-top:16px">Ответить</button>`;
  }

  if(q.type === 'tf'){
    inner += `<div class="tf-row">
      <button class="option tf" data-v="true"><span class="tf-emoji">✅</span>Верно</button>
      <button class="option tf" data-v="false"><span class="tf-emoji">❌</span>Неверно</button>
    </div>`;
  }

  if(q.type === 'match'){
    state.matchOrder = q.right.map((_,i)=>i).sort(()=>Math.random() - 0.5);
    inner += `<div class="match-list">` + q.left.map((l,i)=>
      `<div class="match-row">
         <div class="match-left">${l}</div>
         <select class="match-select" data-i="${i}">
           <option value="">— выберите —</option>
           ${state.matchOrder.map(ri=>`<option value="${ri}">${q.right[ri]}</option>`).join('')}
         </select>
         <span class="match-mark" id="mark-${i}"></span>
       </div>`).join('') + `</div>
      <button class="btn" id="submitBtn" disabled style="margin-top:16px">Ответить</button>`;
  }

  inner += `<div id="feedback"></div>`;
  app.innerHTML = `<div class="card">${inner}</div>`;

  /* --- Обработчики --- */
  if(q.type === 'single'){
    app.querySelectorAll('.option').forEach(btn => {
      btn.addEventListener('click', () => { if(!state.locked) checkSingle(Number(btn.dataset.i)); });
    });
  }

  if(q.type === 'multi'){
    app.querySelectorAll('.option.check').forEach(btn => {
      btn.addEventListener('click', () => {
        if(state.locked) return;
        btn.classList.toggle('selected');
        const any = app.querySelectorAll('.option.check.selected').length > 0;
        document.getElementById('submitBtn').disabled = !any;
      });
    });
    document.getElementById('submitBtn').addEventListener('click', checkMulti);
  }

  if(q.type === 'tf'){
    app.querySelectorAll('.option.tf').forEach(btn => {
      btn.addEventListener('click', () => {
        if(!state.locked) checkTF(btn.dataset.v === 'true');
      });
    });
  }

  if(q.type === 'match'){
    const selects = [...app.querySelectorAll('.match-select')];
    const btn = document.getElementById('submitBtn');
    selects.forEach(s => s.addEventListener('change', () => {
      btn.disabled = selects.some(x => !x.value);
    }));
    btn.addEventListener('click', checkMatch);
  }

  startTimer();
}

/* =========================================================
   ПРОВЕРКА ОТВЕТОВ
   ========================================================= */
function checkSingle(i){
  const q = QUESTIONS[state.index];
  state.locked = true;
  stopTimer();

  app.querySelectorAll('.option').forEach((b,idx) => {
    b.disabled = true;
    if(idx === q.correct) b.classList.add('correct');
    if(idx === i && i !== q.correct) b.classList.add('wrong');
  });

  const ok = i === q.correct;
  const pts = ok ? 100 + Math.round(state.timeLeft * 2.5) : 0;
  award(ok, q, pts);
}

function checkTF(val){
  const q = QUESTIONS[state.index];
  state.locked = true;
  stopTimer();

  app.querySelectorAll('.option.tf').forEach(b => {
    b.disabled = true;
    const isTrue = b.dataset.v === 'true';
    if(isTrue === q.correct) b.classList.add('correct');
    if(isTrue === val && val !== q.correct) b.classList.add('wrong');
  });

  const ok = val === q.correct;
  const pts = ok ? 100 + Math.round(state.timeLeft * 2.5) : 0;
  award(ok, q, pts);
}

function checkMulti(){
  if(state.locked) return;
  const q = QUESTIONS[state.index];
  state.locked = true;
  stopTimer();

  const selected = [...app.querySelectorAll('.option.check.selected')]
    .map(b => Number(b.dataset.i)).sort((a,b) => a - b);
  const correct = [...q.correct].sort((a,b) => a - b);
  const ok = selected.length === correct.length && selected.every((v,i) => v === correct[i]);

  app.querySelectorAll('.option.check').forEach((b,idx) => {
    b.disabled = true;
    b.classList.remove('selected');
    if(q.correct.includes(idx)) b.classList.add('correct');
    else if(selected.includes(idx)) b.classList.add('wrong');
  });

  const pts = ok ? 150 + Math.round(state.timeLeft * 2.5) : 0;
  award(ok, q, pts);
}

function checkMatch(){
  if(state.locked) return;
  const q = QUESTIONS[state.index];
  state.locked = true;
  stopTimer();

  let allOk = true;
  app.querySelectorAll('.match-select').forEach((s,i) => {
    const ok = Number(s.value) === q.correct[i];
    if(!ok) allOk = false;
    s.disabled = true;
    s.classList.add(ok ? 'ok' : 'bad');
    const m = document.getElementById('mark-' + i);
    m.textContent = ok ? '✔' : '✘';
    m.className = 'match-mark ' + (ok ? 'ok' : 'bad');
  });

  const pts = allOk ? 200 + Math.round(state.timeLeft * 2) : 0;
  award(allOk, q, pts);
}

/* =========================================================
   ВРЕМЯ ВЫШЛО
   ========================================================= */
function timeOut(){
  if(state.locked) return;
  state.locked = true;
  const q = QUESTIONS[state.index];
  revealCorrect(q);
  award(false, q, 0, true);
}

function revealCorrect(q){
  const opts = app.querySelectorAll('.option');
  if(q.type === 'single'){
    opts.forEach((b,i) => { b.disabled = true; if(i === q.correct) b.classList.add('correct'); });
  } else if(q.type === 'multi'){
    opts.forEach((b,i) => { b.disabled = true; if(q.correct.includes(i)) b.classList.add('correct'); });
  } else if(q.type === 'tf'){
    opts.forEach(b => {
      b.disabled = true;
      if((b.dataset.v === 'true') === q.correct) b.classList.add('correct');
    });
  } else if(q.type === 'match'){
    app.querySelectorAll('.match-select').forEach((s,i) => {
      s.value = q.correct[i];
      s.disabled = true;
      s.classList.add('ok');
      const m = document.getElementById('mark-' + i);
      if(m){ m.textContent = '✔'; m.className = 'match-mark ok'; }
    });
  }
}

/* =========================================================
   ИТОГ ВОПРОСА
   ========================================================= */
function award(ok, q, points, isTimeout = false){
  if(ok) state.correctCount++;
  state.score += points;

  document.getElementById('scoreStat').textContent = '⭐ ' + state.score;
  progressBar.style.width = ((state.index + 1) / QUESTIONS.length * 100) + '%';

  const isLast = state.index === QUESTIONS.length - 1;
  const fb = document.getElementById('feedback');
  fb.innerHTML = `
    <div class="feedback ${ok ? 'ok' : 'bad'}">
      <div class="fb-head">${isTimeout ? '⏰ Время вышло!' : (ok ? '✅ Верно!' : '❌ Неверно')}</div>
      <div class="fb-expl">${q.expl}</div>
      <div class="fb-foot">
        <span class="fb-points">${points > 0 ? '+' + points + ' очков' : '+0 очков'}</span>
        <button class="btn" id="nextBtn">${isLast ? 'К диплому 🎓' : 'Дальше →'}</button>
      </div>
    </div>`;

  document.getElementById('nextBtn').addEventListener('click', next);
  fb.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
}

function next(){
  state.index++;
  if(state.index < QUESTIONS.length) showQuestion();
  else showDiploma();
}

/* =========================================================
   ДИПЛОМ
   ========================================================= */
function getRank(p){
  if(p === 100) return { title: 'Магистр кошачьих наук', emoji: '🎓' };
  if(p >= 85)   return { title: 'Эксперт-котолог',         emoji: '🏆' };
  if(p >= 70)   return { title: 'Старший котолог',         emoji: '🥇' };
  if(p >= 55)   return { title: 'Котолог-практик',         emoji: '🥈' };
  if(p >= 40)   return { title: 'Юный котолог',            emoji: '🥉' };
  return           { title: 'Ученик академии',          emoji: '🐾' };
}

function showDiploma(){
  stopTimer();
  topbar.style.display = 'none';

  const total = QUESTIONS.length;
  const pct = Math.round(state.correctCount / total * 100);
  const rank = getRank(pct);
  const date = new Date().toLocaleDateString('ru-RU', { day: 'numeric', month: 'long', year: 'numeric' });
  const no = 'КШ-' + Math.floor(100000 + Math.random() * 900000) + '/' + new Date().getFullYear();

  app.innerHTML = `
    <div class="card result-card no-print-head">
      <h2 class="result-h">Квест пройден! 🎉</h2>
      <p class="result-sub">Вот твой именной диплом. Его можно распечатать или сохранить в PDF.</p>
    </div>

    <div id="diploma">
      <span class="dip-corner tl">🐾</span>
      <span class="dip-corner tr">🐾</span>
      <span class="dip-corner bl">🐾</span>
      <span class="dip-corner br">🐾</span>

      <div class="dip-academy">Академия кошачьих наук</div>
      <div class="dip-title">ДИПЛОМ</div>
      <div class="dip-sub">о прохождении курса «Типы кошек»</div>

      <div class="dip-name">${esc(state.name)}</div>

      <div class="dip-text">
        успешно прошёл(ла) все испытания квеста,<br>
        верно ответив на <b>${state.correctCount} из ${total}</b> вопросов
      </div>

      <div class="dip-rank">${rank.emoji} ${rank.title}</div>

      <div class="dip-stats">
        <div><span>${pct}%</span><small>результат</small></div>
        <div><span>${state.score}</span><small>очков</small></div>
        <div><span>${state.correctCount}/${total}</span><small>верно</small></div>
      </div>

      <div class="dip-footer">
        <div class="dip-date">${date}</div>
        <div class="dip-seal">🐈<small>печать академии</small></div>
        <div class="dip-sign">Ректор<br><b>Кот Учёный</b></div>
      </div>

      <div class="dip-no">Диплом № ${no}</div>
    </div>

    <div class="actions no-print">
      <button class="btn" id="printBtn">🖨 Распечатать / PDF</button>
      <button class="btn ghost" id="againBtn">🔄 Пройти заново</button>
    </div>
    <p class="print-hint no-print">Совет: в окне печати выбери «Сохранить как PDF», чтобы получить файл.</p>
  `;

  document.getElementById('printBtn').addEventListener('click', () => window.print());
  document.getElementById('againBtn').addEventListener('click', showStart);

  confetti(pct >= 60 ? 40 : 16);
}

/* =========================================================
   КОНФЕТТИ
   ========================================================= */
function confetti(count){
  const emojis = ['🐾','⭐','🐱','✨','🐈','💛','🏆'];
  for(let i = 0; i < count; i++){
    const el = document.createElement('div');
    el.textContent = emojis[Math.floor(Math.random() * emojis.length)];
    el.style.cssText = `
      position:fixed; left:${Math.random() * 100}vw; top:-50px;
      font-size:${16 + Math.random() * 24}px; pointer-events:none; z-index:9999;
      transition:transform ${1.8 + Math.random() * 1.6}s linear, opacity 2.6s ease;
    `;
    document.body.appendChild(el);
    requestAnimationFrame(() => {
      el.style.transform = `translateY(${window.innerHeight + 140}px) rotate(${Math.random() * 720 - 360}deg)`;
      el.style.opacity = '0';
    });
    setTimeout(() => el.remove(), 3600);
  }
}

/* =========================================================
   ЗАПУСК
   ========================================================= */
showStart();
</script>
</body>
</html>
