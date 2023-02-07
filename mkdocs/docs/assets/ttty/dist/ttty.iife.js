var ttty=function(n){"use strict";const t=(n,t,e)=>{const o=document.createElement(n);return t&&(o.className=t),e&&(o.innerHTML=e),o},e=(n,t=!1)=>{n.input.readOnly=!t,n.inputContainer.style.opacity=t?"":"0"};var o,s;(s=o||(o={})).ON_COMMAND="onCommand",s.ON_COMMAND_NOT_FOUND="onCommand404",s.ON_PROCESS_START="onProcessStart",s.ON_PROCESS_END="onProcessStop",s.ON_PROCESS_INTERRUPT="onProcessInterrupt",s.ON_INIT="onInit";const i=(n,t,e)=>{const o=new CustomEvent(n,{detail:e});t.dispatchEvent(o)},r=(n,t)=>{const{print:e}=t,[s,...r]=n.split(" "),a=r.join(" ").match(/('[^']+'|"[^"]+"|[^\s'"]+)/g),l=null===a?[]:a.map((n=>n.replace(/(^['"]|['"]$)/g,""))),c=t.settings.commands[s];c?c.argDescriptions&&c.argDescriptions.length>0&&0===l.length?e(`Usage: ${s} ${c.argDescriptions.map((n=>`[${n}]`)).join(" ")}`):(c.func(t,...l),i(o.ON_COMMAND,t.settings.host,n)):(e(`<span class="terminal-error">command not found: ${s}</span>`),i(o.ON_COMMAND_NOT_FOUND,t.settings.host,n))},a=n=>{const{settings:{host:t}}=n;e(n),n.isProcessRunning=!0,i(o.ON_PROCESS_START,t)},l=n=>{const{input:t,settings:{host:s}}=n;e(n,!0),n.isProcessRunning=!1,t.focus(),i(o.ON_PROCESS_END,s)},c=(n,t)=>{const{history:e,lastHistoryIndex:o}=n,s=e.length-1;let i;t&&0===o||(t||o!==e.length)&&(s<0||(t?(i=o-1,n.input.value=i-1>=0?e[i-1]:""):(i=o+1,n.input.value=e[o]),n.lastHistoryIndex=i))};return n.initTerminal=({host:n,welcomeMessage:e,prompt:s="$: ",historyLength:p=50,enableHelp:m=!0,commands:d})=>{const u={host:n,welcomeMessage:e,prompt:s,historyLength:p,enableHelp:m,commands:d};(()=>{if(0===document.head.querySelectorAll('link[data-type="terminal"]').length){const n=t("style",void 0,'.terminal{overflow-y:auto;overflow-x:hidden;background-color:var(--terminal-bg-color, black);padding:15px;box-sizing:border-box}.terminal *{color:var(--terminal-fg-color, white);font-family:var(--terminal-font, "Courier New", monospace)}.terminal-type{width:100%;display:flex}.terminal-type>span{padding-right:7pt}.terminal-type>input{flex-grow:2;background:transparent;border:0;font-size:inherit;padding:0}.terminal-type>input:focus{border:none;outline:none}.terminal-container>p{margin:0}span.terminal-command{color:var(--terminal-accent-color, #ffff7d)}span.terminal-error{color:var(--terminal-error-color, #cc1010)}');n.setAttribute("data-type","terminal"),n.setAttribute("type","text/css"),document.head.append(n)}})();const{commandContainer:g,input:h,inputContainer:y}=((n,e)=>{n.className="terminal";const o=t("div","terminal-container"),s=t("div","terminal-type"),i=t("span",void 0,e),r=t("input");return r.setAttribute("type","text"),s.append(i),s.append(r),n.append(o),n.append(s),n.addEventListener("click",(()=>r.focus())),{commandContainer:o,input:r,inputContainer:s}})(n,s),f={history:[],lastHistoryIndex:0,isProcessRunning:!1,settings:u,commandContainer:g,inputContainer:y,input:h,print:(n,e=!1)=>((n,e,o,s,i)=>{const r=t("p",void 0,e?i:n);if(e){const e=t("span","terminal-command",n);r.append(e)}o.append(r),s.scrollIntoView()})(n,e,g,h,s),run:n=>r(n,f),start:()=>a(f),stop:()=>l(f),type:(n,e=60,o)=>((n,e,o,s)=>{a(o);const i=t("p");o.commandContainer.append(i);let r=0;const c=()=>{r<n.length&&o.isProcessRunning?(i.innerHTML+=n.charAt(r),r++,setTimeout(c,e)):(s&&s(),l(o))};setTimeout(c,e)})(n,e,f,o)};return m&&(f.settings.commands.help=(n=>({name:"help",description:"shows a full list of all available commands",func:({print:t})=>{for(const e in n.settings.commands)Object.hasOwnProperty.call(n.settings.commands,e)&&t(n.settings.commands[e].name+" - "+n.settings.commands[e].description)}}))(f)),((n,t)=>{const{input:e,print:s}=t;n.addEventListener("keyup",(({key:a,ctrlKey:p})=>{if(p&&"c"===a&&t.isProcessRunning)s("^C"),l(t),i(o.ON_PROCESS_INTERRUPT,n);else{if(t.isProcessRunning)return;if("Enter"===a)return t.lastHistoryIndex=0,e.value.length>0?(s(e.value,!0),(n=>{const{input:{value:t},history:e,settings:{historyLength:o}}=n;t!==e[0]&&(e.length>=o?n.history=[t,...e.slice(0,-1)]:(n.history=[t,...e],n.lastHistoryIndex=0))})(t),r(e.value,t)):s(" ",!0),void(e.value="");if("ArrowUp"===a)return void c(t);"ArrowDown"===a&&c(t,!0)}}))})(n,f),i(o.ON_INIT,n),e&&f.print(e),f},Object.defineProperty(n,"__esModule",{value:!0}),n[Symbol.toStringTag]="Module",n}({});